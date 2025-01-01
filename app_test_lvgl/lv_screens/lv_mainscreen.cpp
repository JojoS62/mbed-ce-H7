#include "./lv_mainscreen.h"
#include <cstdio>
#include <math.h>

static lv_style_t style_counter;
static lv_style_t style_counterlabel;
static void lvParameterScreen_update_task(bool firstStart);

static LV_HCWidget lv_hcWidgetFBH;
static LV_HCWidget lv_hcWidgetEG;
static LV_HCWidget lv_hcWidgetOG;


void LV_HCWidget::createScreen(const char *text, int x, int y) {
    // create common text label
    lv_obj_t* lbl_heatflow = lv_label_create(lv_scr_act());
    lv_label_set_text(lbl_heatflow, text);
    lv_obj_add_style(lbl_heatflow, &style_counterlabel, 0);
    lv_obj_set_width(lbl_heatflow, 200);
    lv_obj_set_pos(lbl_heatflow, x, y);

    // create heatflow value
    lbl_heatflow_val = lv_label_create(lv_scr_act());
    lv_label_set_text(lbl_heatflow_val, "37.0 °C");
    lv_obj_add_style(lbl_heatflow_val, &style_counter, 0);
    lv_obj_set_style_bg_color(lbl_heatflow_val, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN);
    lv_obj_align_to(lbl_heatflow_val, lbl_heatflow, LV_ALIGN_OUT_RIGHT_BOTTOM, 20, 0);
    lv_obj_set_style_pad_left(lbl_heatflow_val, 0, LV_PART_MAIN);

    // create heatreturn value below
    lbl_heatreturn_val = lv_label_create(lv_scr_act());
    lv_obj_add_style(lbl_heatreturn_val, &style_counter, 0);
    lv_obj_align_to(lbl_heatreturn_val, lbl_heatflow_val, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_label_set_text(lbl_heatreturn_val, "22.0 °C");
    lv_obj_set_style_bg_color(lbl_heatreturn_val, lv_palette_main(LV_PALETTE_CYAN), LV_PART_MAIN);

    // move common label between values y pos
    lv_obj_set_pos(lbl_heatflow, x, y + lv_obj_get_height(lbl_heatflow_val)/2);
}

void LV_HCWidget::setValueHeatFlow(float val) {
    if (val != heatflow_val_old) {
        char s[16];
        snprintf(s, sizeof(s), "%5.1f °C", val);
        lv_label_set_text(lbl_heatflow_val, s);
        heatflow_val_old = val;
    }
}

void LV_HCWidget::setValueHeatReturn(float val) {
    if (val != heatreturn_val_old) {
        char s[16];
        snprintf(s, sizeof(s), "%5.1f °C", val);
        lv_label_set_text(lbl_heatreturn_val, s);
        heatreturn_val_old = val;
    }
}


static void btn_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t* btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        // lv_obj_t* label = lv_obj_get_child(btn, 0);
        //lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

static void event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        uint32_t id = lv_buttonmatrix_get_selected_button(obj);
        const char* txt = lv_btnmatrix_get_btn_text(obj, id);

        LV_LOG_USER("%s was pressed\n", txt);
    }
}


// static const char* btnm_map[] = { LV_SYMBOL_PLAY, LV_SYMBOL_STOP, LV_SYMBOL_LEFT, LV_SYMBOL_RIGHT, LV_SYMBOL_CUT, LV_SYMBOL_SETTINGS, ""};

/**
 * Create a button with a label and react on click event.
 */
void lv_mainscreen(void)
{
    // style for large counters
    lv_style_init(&style_counter);
    lv_style_set_radius(&style_counter, 5);
    lv_style_set_width(&style_counter, 140);
    lv_style_set_height(&style_counter, 50);
    lv_style_set_pad_ver(&style_counter, 5);
    lv_style_set_pad_right(&style_counter, 5);
    lv_style_set_text_font(&style_counter, &lv_font_montserrat_28);
    lv_style_set_text_align(&style_counter, LV_TEXT_ALIGN_RIGHT);
    lv_style_set_bg_opa(&style_counter, LV_OPA_COVER);

    // style for large counterlabel
    lv_style_init(&style_counterlabel);
    lv_style_set_height(&style_counterlabel, 50);
    lv_style_set_pad_ver(&style_counterlabel, 5);
    lv_style_set_pad_left(&style_counterlabel, 5);
    lv_style_set_text_font(&style_counterlabel, &lv_font_montserrat_28);

    lv_hcWidgetFBH.createScreen("EG FBH", 0, 10);
    lv_hcWidgetEG.createScreen("EG Statisch", 0, 150);
    lv_hcWidgetOG.createScreen("OG Statisch", 0, 290);

    lv_obj_set_user_data(lv_scr_act(), (void*)lvParameterScreen_update_task);

    // buttonbar
    // lv_obj_t* btnm1 = lv_btnmatrix_create(lv_scr_act());
    // lv_btnmatrix_set_map(btnm1, btnm_map);
    // lv_obj_set_size(btnm1, 320, 60);
    // lv_obj_set_align(btnm1, LV_ALIGN_BOTTOM_MID);

    // lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);
}

static void lvParameterScreen_update_task(bool firstStart)
{
    // create some random values
    static auto rnd = []() -> float { return (float)rand() / RAND_MAX; };
    float temperature1 = rnd() * 37.0f;
    lv_hcWidgetFBH.setValueHeatFlow(temperature1);
}


