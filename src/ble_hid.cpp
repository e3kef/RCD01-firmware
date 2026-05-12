#include "ble_hid.h"

#include <string.h>

#include "btstack.h"
#include "pico/btstack_cyw43.h"
#include "pico/cyw43_arch.h"

#include "ble/gatt-service/battery_service_server.h"
#include "ble/gatt-service/device_information_service_server.h"
#include "ble/gatt-service/hids_device.h"

#include "ble_profile.h"

static btstack_packet_callback_registration_t hci_event_callback_registration;
static btstack_packet_callback_registration_t sm_event_callback_registration;

static hci_con_handle_t con_handle = HCI_CON_HANDLE_INVALID;
static uint8_t protocol_mode = 1;
static bool input_report_enabled = false;
static bool boot_keyboard_enabled = false;
static bool ble_started = false;

static bool pending_send = false;
static uint8_t pending_report[8];

static const uint8_t hid_descriptor_keyboard_boot_mode[] = {
    0x05, 0x01,
    0x09, 0x06,
    0xa1, 0x01,

    0x85, 0x01,

    0x75, 0x01,
    0x95, 0x08,
    0x05, 0x07,
    0x19, 0xe0,
    0x29, 0xe7,
    0x15, 0x00,
    0x25, 0x01,
    0x81, 0x02,

    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x03,

    0x95, 0x05,
    0x75, 0x01,
    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x05,
    0x91, 0x02,

    0x95, 0x01,
    0x75, 0x03,
    0x91, 0x03,

    0x95, 0x06,
    0x75, 0x08,
    0x15, 0x00,
    0x25, 0xff,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0xff,
    0x81, 0x00,

    0xc0,
};

static const uint8_t adv_data[] = {
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
    0x0a, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME,
    'R', 'C', 'D', '0', '1', ' ', 'B', 'L', 'E',
    0x03, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS,
    ORG_BLUETOOTH_SERVICE_HUMAN_INTERFACE_DEVICE & 0xff,
    ORG_BLUETOOTH_SERVICE_HUMAN_INTERFACE_DEVICE >> 8,
    0x03, BLUETOOTH_DATA_TYPE_APPEARANCE, 0xC1, 0x03,
};

static bool subscribed(){
    return input_report_enabled || boot_keyboard_enabled;
}

static void send_pending_report(){
    if(!pending_send || con_handle == HCI_CON_HANDLE_INVALID){
        return;
    }

    if(protocol_mode == 0){
        hids_device_send_boot_keyboard_input_report(
            con_handle,
            pending_report,
            sizeof(pending_report)
        );
    }else{
        hids_device_send_input_report(
            con_handle,
            pending_report,
            sizeof(pending_report)
        );
    }

    pending_send = false;
}

static void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    (void)channel;
    (void)size;

    if(packet_type != HCI_EVENT_PACKET){
        return;
    }

    switch(hci_event_packet_get_type(packet)){
        case HCI_EVENT_DISCONNECTION_COMPLETE:
            con_handle = HCI_CON_HANDLE_INVALID;
            input_report_enabled = false;
            boot_keyboard_enabled = false;
            pending_send = false;
            break;

        case SM_EVENT_JUST_WORKS_REQUEST:
            sm_just_works_confirm(sm_event_just_works_request_get_handle(packet));
            break;

        case SM_EVENT_NUMERIC_COMPARISON_REQUEST:
            sm_numeric_comparison_confirm(sm_event_numeric_comparison_request_get_handle(packet));
            break;

        case HCI_EVENT_HIDS_META:
            switch(hci_event_hids_meta_get_subevent_code(packet)){
                case HIDS_SUBEVENT_INPUT_REPORT_ENABLE:
                    con_handle = hids_subevent_input_report_enable_get_con_handle(packet);
                    input_report_enabled = hids_subevent_input_report_enable_get_enable(packet) != 0;
                    break;

                case HIDS_SUBEVENT_BOOT_KEYBOARD_INPUT_REPORT_ENABLE:
                    con_handle = hids_subevent_boot_keyboard_input_report_enable_get_con_handle(packet);
                    boot_keyboard_enabled = hids_subevent_boot_keyboard_input_report_enable_get_enable(packet) != 0;
                    break;

                case HIDS_SUBEVENT_PROTOCOL_MODE:
                    protocol_mode = hids_subevent_protocol_mode_get_protocol_mode(packet);
                    break;

                case HIDS_SUBEVENT_CAN_SEND_NOW:
                    send_pending_report();
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void ble_hid_init(){
    if(ble_started){
        return;
    }

    if(cyw43_arch_init() != 0){
        return;
    }

    if(!btstack_cyw43_init(cyw43_arch_async_context())){
        return;
    }

    l2cap_init();

    sm_init();

    // add
    for(int i = 0; i < le_device_db_max_count(); i++){
        le_device_db_remove(i);
    }

    sm_set_io_capabilities(IO_CAPABILITY_NO_INPUT_NO_OUTPUT);
    sm_set_authentication_requirements(SM_AUTHREQ_SECURE_CONNECTION | SM_AUTHREQ_BONDING);

    att_server_init(profile_data, nullptr, nullptr);

    battery_service_server_init(100);
    device_information_service_server_init();

    hids_device_init(0, hid_descriptor_keyboard_boot_mode, sizeof(hid_descriptor_keyboard_boot_mode));

    bd_addr_t null_addr;
    memset(null_addr, 0, sizeof(null_addr));
    gap_advertisements_set_params(0x0030, 0x0030, 0, 0, null_addr, 0x07, 0x00);
    gap_advertisements_set_data(sizeof(adv_data), const_cast<uint8_t*>(adv_data));
    gap_advertisements_enable(1);

    hci_event_callback_registration.callback = &packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);

    sm_event_callback_registration.callback = &packet_handler;
    sm_add_event_handler(&sm_event_callback_registration);

    hids_device_register_packet_handler(packet_handler);

    hci_power_control(HCI_POWER_ON);
    ble_started = true;
}

void ble_hid_task(){
}

bool ble_hid_ready(){
    return ble_started
        && con_handle != HCI_CON_HANDLE_INVALID
        && subscribed()
        && !pending_send;
}

bool ble_hid_send_report(const KeyboardReport& report){
    if(!ble_hid_ready()){
        return false;
    }

    pending_report[0] = report.modifiers;
    pending_report[1] = 0;
    memcpy(&pending_report[2], report.keycodes, 6);

    pending_send = true;
    hids_device_request_can_send_now_event(con_handle);
    return true;
}

bool ble_hid_send_release(){
    if(!ble_hid_ready()){
        return false;
    }

    memset(pending_report, 0, sizeof(pending_report));

    pending_send = true;
    hids_device_request_can_send_now_event(con_handle);
    return true;
}