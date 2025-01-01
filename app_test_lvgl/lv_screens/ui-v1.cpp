// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: HeaterController

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Screen1_Panel1;
lv_obj_t * ui_Screen1_Slider1;
lv_obj_t * ui_Screen1_Label1;
lv_obj_t * ui_Screen1_Slider2;
lv_obj_t * ui_Screen1_TempV;
lv_obj_t * ui_Screen1_TempR;
lv_obj_t * ui_Screen1_Scale;
lv_obj_t * ui_Screen1_Unit;
lv_obj_t * ui_Screen1_Label5;
lv_obj_t * ui_Screen1_Label2;
lv_obj_t * ui_Screen1_Panel2;
lv_obj_t * ui_Screen1_Slider3;
lv_obj_t * ui_Screen1_Label3;
lv_obj_t * ui_Screen1_Slider4;
lv_obj_t * ui_Screen1_TempV1;
lv_obj_t * ui_Screen1_TempR1;
lv_obj_t * ui_Screen1_Scale1;
lv_obj_t * ui_Screen1_Unit1;
lv_obj_t * ui_Screen1_Label4;
lv_obj_t * ui_Screen1_Label6;
lv_obj_t * ui_Screen1_Panel3;
lv_obj_t * ui_Screen1_Slider5;
lv_obj_t * ui_Screen1_Label7;
lv_obj_t * ui_Screen1_Slider6;
lv_obj_t * ui_Screen1_TempV2;
lv_obj_t * ui_Screen1_TempR2;
lv_obj_t * ui_Screen1_Scale2;
lv_obj_t * ui_Screen1_Unit2;
lv_obj_t * ui_Screen1_Label8;
lv_obj_t * ui_Screen1_Label9;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x525252), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Panel1, 130);
    lv_obj_set_height(ui_Screen1_Panel1, 470);
    lv_obj_set_x(ui_Screen1_Panel1, 5);
    lv_obj_set_y(ui_Screen1_Panel1, 5);
    lv_obj_clear_flag(ui_Screen1_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Screen1_Panel1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Panel1, lv_color_hex(0xACADAF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Slider1 = lv_slider_create(ui_Screen1_Panel1);
    lv_slider_set_range(ui_Screen1_Slider1, 0, 80);
    lv_slider_set_value(ui_Screen1_Slider1, 35, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Screen1_Slider1) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Screen1_Slider1, 0,
                                                                                                    LV_ANIM_OFF);
    lv_obj_set_width(ui_Screen1_Slider1, 23);
    lv_obj_set_height(ui_Screen1_Slider1, 376);
    lv_obj_set_x(ui_Screen1_Slider1, 35); 
    lv_obj_set_y(ui_Screen1_Slider1, 14);
    lv_obj_set_align(ui_Screen1_Slider1, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_Screen1_Slider1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider1, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen1_Slider1, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Screen1_Slider1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Screen1_Slider1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen1_Slider1, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Screen1_Slider1, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider1, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Slider1, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Screen1_Slider1, true, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Screen1_Slider1, &ui_img_icn_play_rev_png, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_Screen1_Slider1, lv_color_hex(0xE0E0E0), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_Screen1_Slider1, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Screen1_Label1 = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label1, 0);
    lv_obj_set_y(ui_Screen1_Label1, -14);
    lv_obj_set_align(ui_Screen1_Label1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen1_Label1, "EG FBH");
    lv_obj_set_style_radius(ui_Screen1_Label1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Label1, lv_color_hex(0xF5F7F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Label1, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Label1, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Label1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Label1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Slider2 = lv_slider_create(ui_Screen1_Panel1);
    lv_slider_set_range(ui_Screen1_Slider2, 0, 80);
    lv_slider_set_value(ui_Screen1_Slider2, 40, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Screen1_Slider2) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Screen1_Slider2, 0,
                                                                                                    LV_ANIM_OFF);
    lv_obj_set_width(ui_Screen1_Slider2, 23);
    lv_obj_set_height(ui_Screen1_Slider2, 376);
    lv_obj_set_x(ui_Screen1_Slider2, -35);
    lv_obj_set_y(ui_Screen1_Slider2, 14);
    lv_obj_set_align(ui_Screen1_Slider2, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_Screen1_Slider2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider2, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen1_Slider2, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Screen1_Slider2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Screen1_Slider2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen1_Slider2, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Screen1_Slider2, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider2, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider2, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Slider2, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Screen1_Slider2, true, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Screen1_Slider2, &ui_img_icn_play_png, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_Screen1_Slider2, lv_color_hex(0xE0E0E0), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_Screen1_Slider2, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Screen1_TempV = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_TempV, 55);
    lv_obj_set_height(ui_Screen1_TempV, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_TempV, -32);
    lv_obj_set_y(ui_Screen1_TempV, -4);
    lv_obj_set_align(ui_Screen1_TempV, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_TempV, "40.2 ");
    lv_obj_set_style_text_align(ui_Screen1_TempV, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_TempV, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_TempV, lv_color_hex(0xE5E3E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_TempV, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_TempR = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_TempR, 55);
    lv_obj_set_height(ui_Screen1_TempR, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_TempR, 32);
    lv_obj_set_y(ui_Screen1_TempR, -4);
    lv_obj_set_align(ui_Screen1_TempR, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_TempR, "35.6");
    lv_obj_set_style_text_align(ui_Screen1_TempR, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_TempR, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_TempR, lv_color_hex(0xE5E3E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_TempR, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Scale = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_height(ui_Screen1_Scale, 380);
    lv_obj_set_width(ui_Screen1_Scale, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_x(ui_Screen1_Scale, 0);
    lv_obj_set_y(ui_Screen1_Scale, 10);
    lv_obj_set_align(ui_Screen1_Scale, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen1_Scale, "80\n70\n60\n50\n40\n30\n20\n10\n0");
    lv_obj_set_style_text_letter_space(ui_Screen1_Scale, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_Screen1_Scale, 31, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1_Scale, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_Scale, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Unit = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Unit, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Unit, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Unit, -2);
    lv_obj_set_y(ui_Screen1_Unit, 20);
    lv_obj_set_align(ui_Screen1_Unit, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Unit, "°C");

    ui_Screen1_Label5 = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label5, -31);
    lv_obj_set_y(ui_Screen1_Label5, 20);
    lv_obj_set_align(ui_Screen1_Label5, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Label5, "V");

    ui_Screen1_Label2 = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label2, 27);
    lv_obj_set_y(ui_Screen1_Label2, 20);
    lv_obj_set_align(ui_Screen1_Label2, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Label2, "R");

    ui_Screen1_Panel2 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Panel2, 130);
    lv_obj_set_height(ui_Screen1_Panel2, 470);
    lv_obj_set_x(ui_Screen1_Panel2, 140);
    lv_obj_set_y(ui_Screen1_Panel2, 5);
    lv_obj_clear_flag(ui_Screen1_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Screen1_Panel2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Panel2, lv_color_hex(0xACADAF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Slider3 = lv_slider_create(ui_Screen1_Panel2);
    lv_slider_set_range(ui_Screen1_Slider3, 0, 80);
    lv_slider_set_value(ui_Screen1_Slider3, 35, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Screen1_Slider3) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Screen1_Slider3, 0,
                                                                                                    LV_ANIM_OFF);
    lv_obj_set_width(ui_Screen1_Slider3, 23);
    lv_obj_set_height(ui_Screen1_Slider3, 376);
    lv_obj_set_x(ui_Screen1_Slider3, 35);
    lv_obj_set_y(ui_Screen1_Slider3, 14);
    lv_obj_set_align(ui_Screen1_Slider3, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_Screen1_Slider3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider3, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen1_Slider3, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Screen1_Slider3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Screen1_Slider3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen1_Slider3, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Screen1_Slider3, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider3, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider3, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Slider3, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider3, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Screen1_Slider3, true, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Screen1_Slider3, &ui_img_icn_play_rev_png, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_Screen1_Slider3, lv_color_hex(0xE0E0E0), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_Screen1_Slider3, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Screen1_Label3 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_width(ui_Screen1_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label3, 0);
    lv_obj_set_y(ui_Screen1_Label3, -14);
    lv_obj_set_align(ui_Screen1_Label3, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen1_Label3, "EG Statisch");
    lv_obj_set_style_radius(ui_Screen1_Label3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Label3, lv_color_hex(0xF5F7F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Label3, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Label3, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Label3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Label3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Slider4 = lv_slider_create(ui_Screen1_Panel2);
    lv_slider_set_range(ui_Screen1_Slider4, 0, 80);
    lv_slider_set_value(ui_Screen1_Slider4, 40, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Screen1_Slider4) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Screen1_Slider4, 0,
                                                                                                    LV_ANIM_OFF);
    lv_obj_set_width(ui_Screen1_Slider4, 23);
    lv_obj_set_height(ui_Screen1_Slider4, 376);
    lv_obj_set_x(ui_Screen1_Slider4, -35);
    lv_obj_set_y(ui_Screen1_Slider4, 14);
    lv_obj_set_align(ui_Screen1_Slider4, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_Screen1_Slider4, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider4, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen1_Slider4, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Screen1_Slider4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Screen1_Slider4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen1_Slider4, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Screen1_Slider4, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider4, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider4, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Slider4, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider4, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Screen1_Slider4, true, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Screen1_Slider4, &ui_img_icn_play_png, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_Screen1_Slider4, lv_color_hex(0xE0E0E0), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_Screen1_Slider4, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Screen1_TempV1 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_width(ui_Screen1_TempV1, 55);
    lv_obj_set_height(ui_Screen1_TempV1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_TempV1, -32);
    lv_obj_set_y(ui_Screen1_TempV1, -4);
    lv_obj_set_align(ui_Screen1_TempV1, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_TempV1, "40.2 ");
    lv_obj_set_style_text_align(ui_Screen1_TempV1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_TempV1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_TempV1, lv_color_hex(0xE5E3E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_TempV1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_TempR1 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_width(ui_Screen1_TempR1, 55);
    lv_obj_set_height(ui_Screen1_TempR1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_TempR1, 32);
    lv_obj_set_y(ui_Screen1_TempR1, -4);
    lv_obj_set_align(ui_Screen1_TempR1, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_TempR1, "35.6");
    lv_obj_set_style_text_align(ui_Screen1_TempR1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_TempR1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_TempR1, lv_color_hex(0xE5E3E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_TempR1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Scale1 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_height(ui_Screen1_Scale1, 380);
    lv_obj_set_width(ui_Screen1_Scale1, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_x(ui_Screen1_Scale1, 0);
    lv_obj_set_y(ui_Screen1_Scale1, 10);
    lv_obj_set_align(ui_Screen1_Scale1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen1_Scale1, "80\n70\n60\n50\n40\n30\n20\n10\n0");
    lv_obj_set_style_text_letter_space(ui_Screen1_Scale1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_Screen1_Scale1, 31, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1_Scale1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_Scale1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Unit1 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_width(ui_Screen1_Unit1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Unit1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Unit1, -2);
    lv_obj_set_y(ui_Screen1_Unit1, 20);
    lv_obj_set_align(ui_Screen1_Unit1, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Unit1, "°C");

    ui_Screen1_Label4 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_width(ui_Screen1_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label4, -31);
    lv_obj_set_y(ui_Screen1_Label4, 20);
    lv_obj_set_align(ui_Screen1_Label4, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Label4, "V");

    ui_Screen1_Label6 = lv_label_create(ui_Screen1_Panel2);
    lv_obj_set_width(ui_Screen1_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label6, 27);
    lv_obj_set_y(ui_Screen1_Label6, 20);
    lv_obj_set_align(ui_Screen1_Label6, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Label6, "R");

    ui_Screen1_Panel3 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Panel3, 130);
    lv_obj_set_height(ui_Screen1_Panel3, 470);
    lv_obj_set_x(ui_Screen1_Panel3, 275);
    lv_obj_set_y(ui_Screen1_Panel3, 5);
    lv_obj_clear_flag(ui_Screen1_Panel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Screen1_Panel3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Panel3, lv_color_hex(0xACADAF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Slider5 = lv_slider_create(ui_Screen1_Panel3);
    lv_slider_set_range(ui_Screen1_Slider5, 0, 80);
    lv_slider_set_value(ui_Screen1_Slider5, 35, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Screen1_Slider5) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Screen1_Slider5, 0,
                                                                                                    LV_ANIM_OFF);
    lv_obj_set_width(ui_Screen1_Slider5, 23);
    lv_obj_set_height(ui_Screen1_Slider5, 376);
    lv_obj_set_x(ui_Screen1_Slider5, 35);
    lv_obj_set_y(ui_Screen1_Slider5, 14);
    lv_obj_set_align(ui_Screen1_Slider5, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_Screen1_Slider5, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider5, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen1_Slider5, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Screen1_Slider5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Screen1_Slider5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen1_Slider5, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Screen1_Slider5, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider5, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider5, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Slider5, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider5, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Screen1_Slider5, true, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Screen1_Slider5, &ui_img_icn_play_rev_png, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_Screen1_Slider5, lv_color_hex(0xE0E0E0), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_Screen1_Slider5, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Screen1_Label7 = lv_label_create(ui_Screen1_Panel3);
    lv_obj_set_width(ui_Screen1_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label7, 0);
    lv_obj_set_y(ui_Screen1_Label7, -14);
    lv_obj_set_align(ui_Screen1_Label7, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen1_Label7, "OG Statisch");
    lv_obj_set_style_radius(ui_Screen1_Label7, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Label7, lv_color_hex(0xF5F7F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen1_Label7, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen1_Label7, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen1_Label7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen1_Label7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Slider6 = lv_slider_create(ui_Screen1_Panel3);
    lv_slider_set_range(ui_Screen1_Slider6, 0, 80);
    lv_slider_set_value(ui_Screen1_Slider6, 40, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Screen1_Slider6) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Screen1_Slider6, 0,
                                                                                                    LV_ANIM_OFF);
    lv_obj_set_width(ui_Screen1_Slider6, 23);
    lv_obj_set_height(ui_Screen1_Slider6, 376);
    lv_obj_set_x(ui_Screen1_Slider6, -35);
    lv_obj_set_y(ui_Screen1_Slider6, 14);
    lv_obj_set_align(ui_Screen1_Slider6, LV_ALIGN_TOP_MID);
    lv_obj_set_style_radius(ui_Screen1_Slider6, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider6, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Screen1_Slider6, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Screen1_Slider6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Screen1_Slider6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Screen1_Slider6, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Screen1_Slider6, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Slider6, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider6, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Screen1_Slider6, lv_color_hex(0x0000FF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Slider6, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_Screen1_Slider6, true, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Screen1_Slider6, &ui_img_icn_play_png, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_Screen1_Slider6, lv_color_hex(0xE0E0E0), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_Screen1_Slider6, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Screen1_TempV2 = lv_label_create(ui_Screen1_Panel3);
    lv_obj_set_width(ui_Screen1_TempV2, 55);
    lv_obj_set_height(ui_Screen1_TempV2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_TempV2, -32);
    lv_obj_set_y(ui_Screen1_TempV2, -4);
    lv_obj_set_align(ui_Screen1_TempV2, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_TempV2, "40.2 ");
    lv_obj_set_style_text_align(ui_Screen1_TempV2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_TempV2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_TempV2, lv_color_hex(0xE5E3E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_TempV2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_TempR2 = lv_label_create(ui_Screen1_Panel3);
    lv_obj_set_width(ui_Screen1_TempR2, 55);
    lv_obj_set_height(ui_Screen1_TempR2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_TempR2, 32);
    lv_obj_set_y(ui_Screen1_TempR2, -4);
    lv_obj_set_align(ui_Screen1_TempR2, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_TempR2, "35.6");
    lv_obj_set_style_text_align(ui_Screen1_TempR2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_TempR2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_TempR2, lv_color_hex(0xE5E3E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_TempR2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Scale2 = lv_label_create(ui_Screen1_Panel3);
    lv_obj_set_height(ui_Screen1_Scale2, 380);
    lv_obj_set_width(ui_Screen1_Scale2, LV_SIZE_CONTENT);   /// 20
    lv_obj_set_x(ui_Screen1_Scale2, 0);
    lv_obj_set_y(ui_Screen1_Scale2, 10);
    lv_obj_set_align(ui_Screen1_Scale2, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen1_Scale2, "80\n70\n60\n50\n40\n30\n20\n10\n0");
    lv_obj_set_style_text_letter_space(ui_Screen1_Scale2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_Screen1_Scale2, 31, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1_Scale2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen1_Scale2, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Unit2 = lv_label_create(ui_Screen1_Panel3);
    lv_obj_set_width(ui_Screen1_Unit2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Unit2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Unit2, -2);
    lv_obj_set_y(ui_Screen1_Unit2, 20);
    lv_obj_set_align(ui_Screen1_Unit2, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Unit2, "°C");

    ui_Screen1_Label8 = lv_label_create(ui_Screen1_Panel3);
    lv_obj_set_width(ui_Screen1_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label8, -31);
    lv_obj_set_y(ui_Screen1_Label8, 20);
    lv_obj_set_align(ui_Screen1_Label8, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Label8, "V");

    ui_Screen1_Label9 = lv_label_create(ui_Screen1_Panel3);
    lv_obj_set_width(ui_Screen1_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label9, 27);
    lv_obj_set_y(ui_Screen1_Label9, 20);
    lv_obj_set_align(ui_Screen1_Label9, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Screen1_Label9, "R");

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
