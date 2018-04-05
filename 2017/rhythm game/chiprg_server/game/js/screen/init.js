var screenInit = {
  loadTimer: new RGtimer(),
  titleImage: "",

  preload: function(){

    // Enable scale is zoomed
    game.scale.scaleMode = Phaser.ScaleManager.SHOW_ALL;
    game.scale.pageAlignHorizontally = true;
    game.scale.pageAlignVertically = true;

    // Disable Anti-ailas when scale is zoomed
    Phaser.Canvas.setImageRenderingCrisp(game.canvas); // for Canvas renderer
    PIXI.scaleModes.DEFAULT = PIXI.scaleModes.NEAREST; // for webGL renderer
    // Phaser.Canvas.setSmoothingEnabled(game.context, false); // Dosen't work on Chrome.

    // Load Bitmap Font
    game.load.bitmapFont(
      'font57', PATH.FONT + 'font57.png', PATH.FONT + 'font57.xml');
    game.load.bitmapFont(
      'font79', PATH.FONT + 'font79.png', PATH.FONT + 'font79.xml');

    // Load Virtual Keyboard IMG
    game.load.spritesheet(
      'keyboard', PATH.uiPath(PATH.uiName)+ 'keyboard/keyboard.png', 300, 80);
    game.load.spritesheet(
      'textbox', PATH.uiPath(PATH.uiName)+ 'keyboard/textbox.png', 300, 20);
    game.load.spritesheet(
      'beam', PATH.uiPath(PATH.uiName)+ 'keyboard/beam.png', 1, 9);
    game.load.spritesheet(
      'key20', PATH.uiPath(PATH.uiName)+ 'keyboard/key20.png', 20, 20);
    game.load.spritesheet(
      'key30', PATH.uiPath(PATH.uiName)+ 'keyboard/key30.png', 30, 20);
    game.load.spritesheet(
      'key40', PATH.uiPath(PATH.uiName)+ 'keyboard/key40.png', 40, 20);
    game.load.spritesheet(
      'key50', PATH.uiPath(PATH.uiName)+ 'keyboard/key50.png', 50, 20);
    game.load.spritesheet(
      'sel20', PATH.uiPath(PATH.uiName)+ 'keyboard/sel20.png', 20, 20);
    game.load.spritesheet(
      'sel30', PATH.uiPath(PATH.uiName)+ 'keyboard/sel30.png', 30, 20);
    game.load.spritesheet(
      'sel40', PATH.uiPath(PATH.uiName)+ 'keyboard/sel40.png', 40, 20);
    game.load.spritesheet(
      'sel50', PATH.uiPath(PATH.uiName)+ 'keyboard/sel50.png', 50, 20);
    game.load.spritesheet(
      'kbdDialogbox', PATH.uiPath(PATH.uiName)+ 'keyboard/dialogbox.png', 300, 80);
    game.load.spritesheet(
      'kbdDialogbutton', PATH.uiPath(PATH.uiName)+ 'keyboard/dialogbutton.png', 80, 20);

    // Load Logo
    game.load.image(
      'teamLogo', PATH.IMG + 'title/studio2AOE_180p.png');
    game.load.image(
      'titleImage', PATH.IMG + 'title/titleImage.png');
  },

  create: function(){
    this.loadTimer.start(120);
    this.titleImage = game.add.image(0, 0, 'teamLogo');

    // Setup Multitouch
    game.input.addPointer();
    game.input.addPointer();
    game.input.addPointer();
    game.input.addPointer();
    RGinput.touch.mo = game.input.mousePointer;
    RGinput.touch.t1 = game.input.pointer1;
    RGinput.touch.t2 = game.input.pointer2;
    RGinput.touch.t3 = game.input.pointer3;
    RGinput.touch.t4 = game.input.pointer4;
    RGinput.touch.t5 = game.input.pointer5;
    RGinput.touch.t6 = game.input.pointer6;

    // Setup Default Gamepad Buttons
    game.input.gamepad.start();
    RGinput.stage.pad1      = Phaser.Gamepad.XBOX360_DPAD_UP;
    RGinput.stage.pad2      = Phaser.Gamepad.XBOX360_DPAD_RIGHT;
    RGinput.stage.pad3      = Phaser.Gamepad.XBOX360_X;
    RGinput.stage.pad4      = Phaser.Gamepad.XBOX360_Y;
    RGinput.stage.padL      = Phaser.Gamepad.XBOX360_LEFT_BUMPER;
    RGinput.stage.padR      = Phaser.Gamepad.XBOX360_RIGHT_BUMPER;
    RGinput.stage.padS      = Phaser.Gamepad.XBOX360_START;

    RGinput.menu.padUP      = Phaser.Gamepad.XBOX360_DPAD_UP;
    RGinput.menu.padDOWN    = Phaser.Gamepad.XBOX360_DPAD_DOWN;
    RGinput.menu.padLEFT    = Phaser.Gamepad.XBOX360_DPAD_LEFT;
    RGinput.menu.padRIGHT   = Phaser.Gamepad.XBOX360_DPAD_RIGHT;
    RGinput.menu.padCancel  = Phaser.Gamepad.XBOX360_A;
    RGinput.menu.padOK      = Phaser.Gamepad.XBOX360_B;
    RGinput.menu.padOption1 = Phaser.Gamepad.XBOX360_X;
    RGinput.menu.padOption2 = Phaser.Gamepad.XBOX360_Y;
    RGinput.menu.padHelp    = Phaser.Gamepad.XBOX360_BACK;

    // Setup Default Keyboard Keys
    RGinput.stage.key1      = Phaser.Keyboard.S;
    RGinput.stage.key2      = Phaser.Keyboard.F;
    RGinput.stage.key3      = Phaser.Keyboard.J;
    RGinput.stage.key4      = Phaser.Keyboard.L;
    RGinput.stage.keyL      = Phaser.Keyboard.E;
    RGinput.stage.keyR      = Phaser.Keyboard.I;
    RGinput.stage.keyS      = Phaser.Keyboard.ENTER;

    RGinput.menu.keyUP      = Phaser.Keyboard.UP;
    RGinput.menu.keyDOWN    = Phaser.Keyboard.DOWN;
    RGinput.menu.keyLEFT    = Phaser.Keyboard.LEFT;
    RGinput.menu.keyRIGHT   = Phaser.Keyboard.RIGHT;
    RGinput.menu.keyCancel  = Phaser.Keyboard.ESC;
    RGinput.menu.keyOK      = Phaser.Keyboard.ENTER;
    RGinput.menu.keyOption1 = Phaser.Keyboard.Q;
    RGinput.menu.keyOption2 = Phaser.Keyboard.W;
    RGinput.menu.keyHelp    = Phaser.Keyboard.ONE;

  },

  update: function(){
    if(this.loadTimer.getMsec()>=2000) {
      game.state.start('screenStart');
    }
  }
};