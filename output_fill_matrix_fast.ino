void output_fill_matrix_fast(){
  if (countdown == 0){
    // set pixel
    matrixSetPixel(x,y, true);
    x++;
    if (x > 7){
      x = 0;
      y++;
      if (y > 7){
        clear_matrix_immediatly();
      }
    }
    countdown = TIME_20_MS;
  }
}

