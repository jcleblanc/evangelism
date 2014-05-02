var five = require("johnny-five"),
board = new five.Board();

board.on("ready", function() {
  // Create a new `servo` hardware instance.
  servo = new five.Servo(10);

  servo.to( 90 );
  this.wait(1000, function() {
    servo.sweep();
  });

  (new five.Led(13)).strobe(3000);
});
