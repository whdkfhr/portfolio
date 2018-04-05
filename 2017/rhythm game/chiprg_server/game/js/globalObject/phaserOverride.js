// OVERRIDE SOME FUNCTIONS

// set tight gamepad button justPressed timing (250ms --> 30ms)
var JUST_TIME = 30;

Phaser.DeviceButton.prototype.justPressed = function(duration){
  duration = duration || JUST_TIME;
  return (this.isDown && (this.timeDown + duration) > this.game.time.time);
};
