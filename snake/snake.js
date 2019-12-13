var snakeWidth = 12;
var numBoxes = 50;

var canvasWidth = snakeWidth * numBoxes;

var food = new Array(3);
var foodEaten = false;
//food[0] = x cord
//food[1] = y cord

function setup(){
  createCanvas(canvasWidth, canvasWidth);
  food[0] = random(0, canvasWidth);
  food[1] = random(0, canvasWidth);
}

var x = 700;
var y = 300;
var xV = 2;
var yV = 0;
var speed = 2;

function draw(){
  background(0);
  rect(x, y, snakeWidth, snakeWidth);
  rect(food[0], food[1], snakeWidth, snakeWidth);

  x += xV * speed;
  y += yV * speed;
  if (foodEaten == true) {
    spawnFood();
  }

}

function keyPressed() {
  if(keyCode == 87) {
    xV = 0;
    yV = -1;
  } else if(keyCode == 83){
    xV = 0;
    yV = 1;	
  } else if(keyCode == 65){
    xV = -1;
    yV = 0;
  } else if(keyCode == 68){
    xV = 1;
    yV = 0;
  }
}

function spawnFood(){
  rect(random(0,canvasWidth), random(0, canvasWidth), snakeWidth, snakeWidth);
}