target_sources(app PRIVATE
   screen_controller.cpp
      
   castling_screen.cpp
   draw_screen.cpp
   draw1_screen.cpp
   draw2_screen.cpp
   en_passant_screen.cpp
   error_screen.cpp
   giveup_screen.cpp
   home_screen.cpp
   lose_screen.cpp
   mode_screen.cpp
   open_screen.cpp
   piece_screen.cpp
   promotion_screen.cpp
   settings_screen.cpp
   start_screen.cpp
   time_screen.cpp
   win_screen.cpp

   fonts/lv_font_roboto_16.c
   fonts/lv_font_roboto_26.c
   fonts/lv_font_roboto_36.c
   fonts/lv_font_roboto_46.c

   images/ui_img_chess_blt45_svg_png.cpp
   images/ui_img_chess_nlt45_svg_png.cpp
   images/ui_img_chess_plt45_svg_png.cpp
   images/ui_img_chess_qlt45_svg_png.cpp
   images/ui_img_chess_rlt45_svg_png.cpp
)
