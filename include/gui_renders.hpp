#include <lvgl.h>
#include <exception>
namespace gui{
    void init_button(lv_obj_t *button, lv_style_t *style, lv_style_t *style_pr, 
    lv_coord_t x, lv_coord_t y, lv_coord_t w=1, lv_coord_t h=1);
    void init_cont(lv_obj_t *cont, lv_style_t *style, lv_coord_t x, lv_coord_t y, lv_coord_t w=1, lv_coord_t h=1);
    void init_label(lv_obj_t * label, lv_obj_t *parent, const char *text);
    void init_grid(lv_obj_t *cont, const lv_coord_t col[], const lv_coord_t rows[], lv_coord_t w = 320, lv_coord_t h = 240);
    void init_bar(lv_obj_t *bar, lv_style_t *indic_style, lv_style_t *main_style, lv_coord_t w=15, lv_coord_t h=120);

    void init_info_label(lv_obj_t *grid, lv_obj_t *label, lv_style_t *style, lv_coord_t w=2, lv_coord_t h = 1);

    void init_data_buttons(lv_obj_t *grid, lv_style_t **styles,  lv_style_t **pr_styles, lv_coord_t *xs, lv_event_cb_t *cbs, lv_coord_t y, lv_coord_t w = 2, lv_coord_t h = 1);

    void init_process_data_labels(lv_obj_t *grid, lv_obj_t **labels_data, lv_obj_t *label_state,  lv_style_t *style_data,lv_style_t *style_state, const char **process_values);
    
}