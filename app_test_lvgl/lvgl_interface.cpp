#include "mbed.h"
#include "lvgl.h"
#include "LVGLDispDriverBase.h"
#include "LVGLInputDriverBase.h"
#include "lv_screens/lv_mainscreen.h"
#include "lv_screens/ui.h"

using rtos::Kernel::Clock;
static Ticker tickerLvgl;
static Thread lvglThread(osPriorityBelowNormal, 12*1024, nullptr, "lvgl");
#if defined(LED2)
static DigitalOut  ledGreen(LED2, 1);
#endif    

//
// lv Ticker, executed in interrupt context
//

void fnLvTicker()
{
    lv_tick_inc(2); /*Tell LittlevGL that 2 milliseconds were elapsed*/
}


//
//  sleep and call lvHandler cyclic
//   sleeptime_ms: >0: sleep milliseconds, 0: sleep forever

void sleepWithLvHandler(chrono::milliseconds sleepTime)
{
    Clock::duration_u32 elapsedTime = 0ms;
    Clock::duration_u32 timeSlice = 5ms;

    while (elapsedTime <= sleepTime) {
        lv_task_handler();

        ThisThread::sleep_for(timeSlice);
        if (sleepTime > 0ms) {
            elapsedTime += timeSlice;
        }
    }
}

typedef void (*lv_update_cb_t)(bool);

[[maybe_unused]] static void lv_screen_update(lv_timer_t* timer)
{
	static lv_obj_t* lastScreen = 0;

    lv_display_t* disp = (lv_display_t*)lv_timer_get_user_data(timer);
	lv_obj_t* actScreen = lv_display_get_screen_active(disp);
    if (!actScreen) {
        return;
    }
	bool firstStart = (actScreen != lastScreen);
	lastScreen = actScreen;

    lv_update_cb_t update_cb = (lv_update_cb_t)lv_obj_get_user_data(actScreen);
	if (update_cb) {
		update_cb(firstStart);
	}
}

void btn_event_cb(lv_event_t * e)
{
    printf("Clicked\n");
}

void create_lv_screen(lv_disp_t* disp) 
{
    lv_obj_t * scr = lv_disp_get_scr_act(disp);

    lv_obj_t * btn = lv_button_create(scr);                            /*Add a button to the current screen*/
    lv_obj_set_size(btn, 100, 50);                                  /*Set its size*/
    lv_obj_center(btn);   
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);                        /*Add a label to the button*/
    lv_label_set_text(label, "hello");                              /*Set the labels text*/
    lv_obj_center(label);                                           /*Align the label to the center*/
}


void lvglThreadFn() {
    while(true) {
#if defined(LED2)
        ledGreen = !ledGreen;
#endif
        sleepWithLvHandler(50ms);
    }
}

void lvgl_interface_init() {
    LVGLDispDriver*  lvglDisplay = LVGLDispDriver::get_target_default_instance();
    //LVGLInputDriver::get_target_default_instance_touchdrv(lvglDisplay);

    // start threads
    tickerLvgl.attach(&fnLvTicker, 2ms);

  	// register update handler. Task will call screen dependent cyclic updates
    lv_timer_create(lv_screen_update, 200,  lvglDisplay->getLVDisp());

    // create_lv_screen(lvglDisplay->getLVDisp());
    // lv_mainscreen();
    ui_init();


    lvglThread.start(lvglThreadFn);
}