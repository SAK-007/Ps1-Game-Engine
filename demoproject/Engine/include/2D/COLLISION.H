int CheckBoxCollision(int box1x,int box1y,int box1h,int box1w,int box2x,int box2y,int box2h,int box2w){
	if (
    box1x < box2x + box2w &&
    box1x + box1w > box2x &&
    box1y < box2y + box2h &&
    box1h + box1y > box2y
  ) 
  {
	  return 1;
  }
  else
  {
	  return 0;
  }
}




int CheckSpriteCollision(int box1x,int box1y,int box1h,int box1w,int box2x,int box2y,int box2h,int box2w){
	if (
    box1x < box2x + box2w &&
    box1x + box1w > box2x &&
    box1y < box2y + box2h &&
    box1h + box1y > box2y
  ) 
  {
	  return 1;
  }
  else
  {
	  return 0;
  }
}