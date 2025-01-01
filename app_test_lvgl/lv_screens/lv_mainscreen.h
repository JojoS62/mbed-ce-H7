#pragma once
/**
 * @file lv_example_get_started.h
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

    /*********************
     *      INCLUDES
     *********************/

#include "lvgl.h"

class LV_HCWidget {
    public:

    LV_HCWidget() {};

    void createScreen(const char *text, int x, int y);
    
    void setValueHeatFlow(float val);
    void setValueHeatReturn(float val);
    
    private:
    lv_obj_t* lbl_heatflow_val;
    float heatflow_val_old;
    lv_obj_t* lbl_heatreturn_val;
    float heatreturn_val_old;
};

     /*********************
      *      DEFINES
      *********************/

      /**********************
       *      TYPEDEFS
       **********************/

       /**********************
        * GLOBAL PROTOTYPES
        **********************/
    void lv_mainscreen(void);

    /**********************
     *      MACROS
     **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

