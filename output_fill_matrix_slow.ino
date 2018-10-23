
// output mode functions
void output_fill_matrix_slow(){
  if (countdown == 0){
    // set pixel
    //clear_matrix_immediatly_without_reset();
    matrixSetPixel(x,y, true);
    x++;
    if (x > 7){
      x = 0;
      y++;
      if (y > 7){
        clear_matrix_immediatly();
      }
    }
    countdown = TIME_200_MS;
  }
}
