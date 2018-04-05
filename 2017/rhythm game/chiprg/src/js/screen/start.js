var screenStart = {

  // STRINGS
  press: "PRESS START / ENTER",

  // OBJECT
  titleImage: "",
  titleText: "",

  // FUNCTIONS
  preload: function(){
    C2TrackerControl.load(C2Trackers.bgmLoop, 'assets/sound/BGM/bgmSelectAccount.mod');
  },

  create: function(){
    C2TrackerControl.play(C2Trackers.bgmLoop);

    // Graphic Setup
    this.titleImage = game.add.button(0, 0, 'titleImage', this.titleTouched, this);
    this.titleText = game.add.bitmapText(100, 112, 'font79', this.press, 9);

    // Gamepad Setup
    pad1 = game.input.gamepad.pad1;
    game.input.gamepad.start();

  },

  update: function(){
    // Press start
    if (pad1.justPressed(Phaser.Gamepad.XBOX360_START) ||
        game.input.keyboard.justPressed(Phaser.Keyboard.ENTER))
      this.goLogin();
  },

  titleTouched: function(titleImage, pointer, isOver){
    if (isOver) this.goLogin();
  },

  goLogin: function(){
    C2TrackerControl.stop(C2Trackers.bgmLoop);
    game.state.start('screenSelectAccount');
  }
};
