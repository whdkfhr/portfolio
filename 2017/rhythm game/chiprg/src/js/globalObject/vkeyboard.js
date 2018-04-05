var Vkeyboard = function(initx, inity){
  this.isOn = true;
  this.isShiftOn = false;
  this.inputMode = 'touch';
  this.x = initx;
  this.y = inity;
  this.img = game.add.sprite(this.x, this.y, 'keyboard', 0);
  this.textbpx = game.add.sprite(this.x, this.y-20, 'textbox', 0);
  this.currentSelPos = 'ESC';
  this.string = '';
  this.text = game.add.bitmapText(this.x+10, this.y-15, 'font79', this.string, 9);
  this.textbeam = game.add.sprite(this.text.x, this.text.y, 'beam', 0);
  this.textbeam.animations.add('beaming');
  this.beaming = function(){
    this.textbeam.animations.play('beaming', 2, true);
  };
  this.stringUpdate = function(){
    this.text.setText(this.string);
    this.textbeam.x = 1+this.text.x+this.string.length*6;
  };
  this.stringInit = function(){
    this.string = "";
    this.stringUpdate();
  };
  this.stringPop = function(){
    this.string = this.string.slice(0, this.string.length-1);
    this.stringUpdate();
  };
  this.stringPush = function(char){
    if(this.string.length>=46){
      this.string.slice(0, 46);
      if(char=='BACK'){
        this.stringPop();
      }
      if(char=='ESC'){
        this.stringInit();
      }
      if(char=='ENTER'){
      }
      return 0;
    }
    if(this.isShiftOn===true){
      switch(char){
      case 'ESC': char = ''; break;
      case 'ONE': char = '!'; break;
      case 'TWO': char = '@'; break;
      case 'THREE': char = '#'; break;
      case 'FOUR': char = '$'; break;
      case 'FIVE': char = '%'; break;
      case 'SIX': char = '^'; break;
      case 'SEVEN': char = '&'; break;
      case 'EIGHT': char = '*'; break;
      case 'NINE': char = '('; break;
      case 'ZERO': char = ')'; break;
      case 'MINUS': char = '_'; break;
      case 'EQUAL': char = '+'; break;
      case 'BACK': char = ''; break;
      case 'GRAVE': char = '~'; break;
      case 'BRKTL': char = '{'; break;
      case 'BRKTR': char = '}'; break;
      case 'PIPE': char = '|'; break;
      case 'COLON': char = ':'; break;
      case 'QUOTE': char = '"'; break;
      case 'ENTER': char = ''; break;
      case 'SHIFT': char = ''; break;
      case 'COMMA': char = '<'; break;
      case 'POINT': char = '>'; break;
      case 'SLASH': char = '?'; break;
      case 'SPACE': char = ''; break;
      }
    }
    else{
      switch(char){
      case 'ESC':
        char = ''; 
        this.stringInit();
        break;
      case 'ONE': char = '1'; break;
      case 'TWO': char = '2'; break;
      case 'THREE': char = '3'; break;
      case 'FOUR': char = '4'; break;
      case 'FIVE': char = '5'; break;
      case 'SIX': char = '6'; break;
      case 'SEVEN': char = '7'; break;
      case 'EIGHT': char = '8'; break;
      case 'NINE': char = '9'; break;
      case 'ZERO': char = '0'; break;
      case 'MINUS': char = '-'; break;
      case 'EQUAL': char = '='; break;
      case 'BACK':
        char = '';
        this.stringPop();
        break;
      case 'GRAVE': char = '`'; break;
      case 'BRKTL': char = '['; break;
      case 'BRKTR': char = ']'; break;
      case 'PIPE': char = '\\'; break;
      case 'COLON': char = ';'; break;
      case 'QUOTE': char = "'"; break;
      case 'ENTER': char = ''; break;
      case 'SHIFT': char = ''; break;
      case 'COMMA': char = ','; break;
      case 'POINT': char = '.'; break;
      case 'SLASH': char = '/'; break;
      case 'SPACE': char = ' '; break;
      case 'Q': char = 'q'; break;
      case 'W': char = 'w'; break;
      case 'E': char = 'e'; break;
      case 'R': char = 'r'; break;
      case 'T': char = 't'; break;
      case 'Y': char = 'y'; break;
      case 'U': char = 'u'; break;
      case 'I': char = 'i'; break;
      case 'O': char = 'o'; break;
      case 'P': char = 'p'; break;
      case 'A': char = 'a'; break;
      case 'S': char = 's'; break;
      case 'D': char = 'd'; break;
      case 'F': char = 'f'; break;
      case 'G': char = 'g'; break;
      case 'H': char = 'h'; break;
      case 'J': char = 'j'; break;
      case 'K': char = 'k'; break;
      case 'L': char = 'l'; break;
      case 'Z': char = 'z'; break;
      case 'X': char = 'x'; break;
      case 'C': char = 'c'; break;
      case 'V': char = 'v'; break;
      case 'B': char = 'b'; break;
      case 'N': char = 'n'; break;
      case 'M': char = 'm'; break;
      }
    }
    if(char.length>1){
      char = '';
    }
    this.string+=char;
    this.stringUpdate();
  };
  this.addKey = function(pos){    
    var obj = {};
    obj.button = game.add.button(pos.x+this.x, pos.y+this.y, 'key'+pos.w,
    function() {
      this.selInit();
      this.inputMode = 'touch';
      this.stringPush(pos.n);
    },
    this, 0, 0, 1, 0);
    return obj;
  };

  this.ESC   = this.addKey(VkeyPos.ESC  );
  this.ONE   = this.addKey(VkeyPos.ONE  );
  this.TWO   = this.addKey(VkeyPos.TWO  );
  this.THREE = this.addKey(VkeyPos.THREE);
  this.FOUR  = this.addKey(VkeyPos.FOUR );
  this.FIVE  = this.addKey(VkeyPos.FIVE );
  this.SIX   = this.addKey(VkeyPos.SIX  );
  this.SEVEN = this.addKey(VkeyPos.SEVEN);
  this.EIGHT = this.addKey(VkeyPos.EIGHT);
  this.NINE  = this.addKey(VkeyPos.NINE );
  this.ZERO  = this.addKey(VkeyPos.ZERO );
  this.MINUS = this.addKey(VkeyPos.MINUS);
  this.EQUAL = this.addKey(VkeyPos.EQUAL);
  this.BACK  = this.addKey(VkeyPos.BACK );

  this.GRAVE = this.addKey(VkeyPos.GRAVE);
  this.Q     = this.addKey(VkeyPos.Q    );
  this.W     = this.addKey(VkeyPos.W    );
  this.E     = this.addKey(VkeyPos.E    );
  this.R     = this.addKey(VkeyPos.R    );
  this.T     = this.addKey(VkeyPos.T    );
  this.Y     = this.addKey(VkeyPos.Y    );
  this.U     = this.addKey(VkeyPos.U    );
  this.I     = this.addKey(VkeyPos.I    );
  this.O     = this.addKey(VkeyPos.O    );
  this.P     = this.addKey(VkeyPos.P    );
  this.BRKTL = this.addKey(VkeyPos.BRKTL);
  this.BRKTR = this.addKey(VkeyPos.BRKTR);
  this.PIPE  = this.addKey(VkeyPos.PIPE );

  this.A     = this.addKey(VkeyPos.A    );
  this.S     = this.addKey(VkeyPos.S    );
  this.D     = this.addKey(VkeyPos.D    );
  this.F     = this.addKey(VkeyPos.F    );
  this.G     = this.addKey(VkeyPos.G    );
  this.H     = this.addKey(VkeyPos.H    );
  this.J     = this.addKey(VkeyPos.J    );
  this.K     = this.addKey(VkeyPos.K    );
  this.L     = this.addKey(VkeyPos.L    );
  this.COLON = this.addKey(VkeyPos.COLON);
  this.QUOTE = this.addKey(VkeyPos.QUOTE);
  this.ENTER = this.addKey(VkeyPos.ENTER);

  this.SHIFT = this.addKey(VkeyPos.SHIFT);
  this.Z     = this.addKey(VkeyPos.Z    );
  this.X     = this.addKey(VkeyPos.X    );
  this.C     = this.addKey(VkeyPos.C    );
  this.V     = this.addKey(VkeyPos.V    );
  this.B     = this.addKey(VkeyPos.B    );
  this.N     = this.addKey(VkeyPos.N    );
  this.M     = this.addKey(VkeyPos.M    );
  this.COMMA = this.addKey(VkeyPos.COMMA);
  this.POINT = this.addKey(VkeyPos.POINT);
  this.SLASH = this.addKey(VkeyPos.SLASH);
  this.SPACE = this.addKey(VkeyPos.SPACE);

  this.sel20 = game.add.image(-340, 0, 'sel20', 0);
  this.sel30 = game.add.image(-350, 0, 'sel30', 0);
  this.sel40 = game.add.image(-360, 0, 'sel40', 0);
  this.sel50 = game.add.image(-370, 0, 'sel50', 0);

  this.selInit = function(){
    this.sel20.x = -340;
    this.sel30.x = -350;
    this.sel40.x = -360;
    this.sel50.x = -370;
  };
  this.selNewPos = function(keyName){
    switch(keyName){
      case 'ESC'   : return VkeyPos.ESC  ;
      case 'ONE'   : return VkeyPos.ONE  ;
      case 'TWO'   : return VkeyPos.TWO  ;
      case 'THREE' : return VkeyPos.THREE;
      case 'FOUR'  : return VkeyPos.FOUR ;
      case 'FIVE'  : return VkeyPos.FIVE ;
      case 'SIX'   : return VkeyPos.SIX  ;
      case 'SEVEN' : return VkeyPos.SEVEN;
      case 'EIGHT' : return VkeyPos.EIGHT;
      case 'NINE'  : return VkeyPos.NINE ;
      case 'ZERO'  : return VkeyPos.ZERO ;
      case 'MINUS' : return VkeyPos.MINUS;
      case 'EQUAL' : return VkeyPos.EQUAL;
      case 'BACK'  : return VkeyPos.BACK ;
      case 'GRAVE' : return VkeyPos.GRAVE;
      case 'Q'     : return VkeyPos.Q    ;
      case 'W'     : return VkeyPos.W    ;
      case 'E'     : return VkeyPos.E    ;
      case 'R'     : return VkeyPos.R    ;
      case 'T'     : return VkeyPos.T    ;
      case 'Y'     : return VkeyPos.Y    ;
      case 'U'     : return VkeyPos.U    ;
      case 'I'     : return VkeyPos.I    ;
      case 'O'     : return VkeyPos.O    ;
      case 'P'     : return VkeyPos.P    ;
      case 'BRKTL' : return VkeyPos.BRKTL;
      case 'BRKTR' : return VkeyPos.BRKTR;
      case 'PIPE'  : return VkeyPos.PIPE ;

      case 'A'     : return VkeyPos.A    ;
      case 'S'     : return VkeyPos.S    ;
      case 'D'     : return VkeyPos.D    ;
      case 'F'     : return VkeyPos.F    ;
      case 'G'     : return VkeyPos.G    ;
      case 'H'     : return VkeyPos.H    ;
      case 'J'     : return VkeyPos.J    ;
      case 'K'     : return VkeyPos.K    ;
      case 'L'     : return VkeyPos.L    ;
      case 'COLON' : return VkeyPos.COLON;
      case 'QUOTE' : return VkeyPos.QUOTE;
      case 'ENTER' : return VkeyPos.ENTER;

      case 'SHIFT' : return VkeyPos.SHIFT;
      case 'Z'     : return VkeyPos.Z    ;
      case 'X'     : return VkeyPos.X    ;
      case 'C'     : return VkeyPos.C    ;
      case 'V'     : return VkeyPos.V    ;
      case 'B'     : return VkeyPos.B    ;
      case 'N'     : return VkeyPos.N    ;
      case 'M'     : return VkeyPos.M    ;
      case 'COMMA' : return VkeyPos.COMMA;
      case 'POINT' : return VkeyPos.POINT;
      case 'SLASH' : return VkeyPos.SLASH;
      case 'SPACE' : return VkeyPos.SPACE;
    }
  };
  this.selSetPos = function(keyname){
    this.selInit();
    this.currentSelPos = keyname;
    var pos = this.selNewPos(keyname);
    if(pos.w == 20){
      this.sel20.x = pos.x+this.x;
      this.sel20.y = pos.y+this.y;
    }
    else if(pos.w == 30){
      this.sel30.x = pos.x+this.x;
      this.sel30.y = pos.y+this.y;
    }
    else if(pos.w == 40){
      this.sel40.x = pos.x+this.x;
      this.sel40.y = pos.y+this.y;
    }
    else if(pos.w == 50){
      this.sel50.x = pos.x+this.x;
      this.sel50.y = pos.y+this.y;
    }
    else {
    }
  };
  this.selMove = function(direction){
    switch(this.currentSelPos){
    case 'ESC'   :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('GRAVE'); break;
      case 'LEFT' : break;
      case 'RIGHT': this.selSetPos('ONE'); break;
      }
      break;
    case 'ONE'   :  
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('Q'); break;
      case 'LEFT' : this.selSetPos('ESC'); break;
      case 'RIGHT': this.selSetPos('TWO'); break;
      }
      break;
    case 'TWO'   :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('W'); break;
      case 'LEFT' : this.selSetPos('ONE'); break;
      case 'RIGHT': this.selSetPos('THREE'); break;
      }
      break;
    case 'THREE' :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('E'); break;
      case 'LEFT' : this.selSetPos('TWO'); break;
      case 'RIGHT': this.selSetPos('FOUR'); break;
      }
      break;
    case 'FOUR'  :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('R'); break;
      case 'LEFT' : this.selSetPos('THREE'); break;
      case 'RIGHT': this.selSetPos('FIVE'); break;
      }
      break;
    case 'FIVE'  :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('T'); break;
      case 'LEFT' : this.selSetPos('FOUR'); break;
      case 'RIGHT': this.selSetPos('SIX'); break;
      }
      break;
    case 'SIX'   :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('Y'); break;
      case 'LEFT' : this.selSetPos('FIVE'); break;
      case 'RIGHT': this.selSetPos('SEVEN'); break;
      }
      break;
    case 'SEVEN' :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('U'); break;
      case 'LEFT' : this.selSetPos('SIX'); break;
      case 'RIGHT': this.selSetPos('EIGHT'); break;
      }
      break;
    case 'EIGHT' :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('I'); break;
      case 'LEFT' : this.selSetPos('SEVEN'); break;
      case 'RIGHT': this.selSetPos('NINE'); break;
      }
      break;
    case 'NINE'  :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('O'); break;
      case 'LEFT' : this.selSetPos('EIGHT'); break;
      case 'RIGHT': this.selSetPos('ZERO'); break;
      }
      break;
    case 'ZERO'  :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('P'); break;
      case 'LEFT' : this.selSetPos('NINE'); break;
      case 'RIGHT': this.selSetPos('MINUS'); break;
      }
      break;
    case 'MINUS' :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('BRKTL'); break;
      case 'LEFT' : this.selSetPos('ZERO'); break;
      case 'RIGHT': this.selSetPos('EQUAL'); break;
      }
      break;
    case 'EQUAL' :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('BRKTR'); break;
      case 'LEFT' : this.selSetPos('MINUS'); break;
      case 'RIGHT': this.selSetPos('BACK'); break;
      }
      break;
    case 'BACK'  :
      switch(direction){
      case 'UP'   : break;
      case 'DOWN' : this.selSetPos('PIPE'); break;
      case 'LEFT' : this.selSetPos('EQUAL'); break;
      case 'RIGHT': break;
      }
      break;
    
    case 'GRAVE' :
      switch(direction){
      case 'UP'   : this.selSetPos('ESC'); break;
      case 'DOWN' : this.selSetPos('SHIFT'); break;
      case 'LEFT' : break;
      case 'RIGHT': this.selSetPos('Q'); break;
      }
      break;
    case 'Q'     :
      switch(direction){
      case 'UP'   : this.selSetPos('ONE'); break;
      case 'DOWN' : this.selSetPos('A'); break;
      case 'LEFT' : this.selSetPos('GRAVE'); break;
      case 'RIGHT': this.selSetPos('W'); break;
      }
      break;
    case 'W'     :
      switch(direction){
      case 'UP'   : this.selSetPos('TWO'); break;
      case 'DOWN' : this.selSetPos('S'); break;
      case 'LEFT' : this.selSetPos('Q'); break;
      case 'RIGHT': this.selSetPos('E'); break;
      }
      break;
    case 'E'     :
      switch(direction){
      case 'UP'   : this.selSetPos('THREE'); break;
      case 'DOWN' : this.selSetPos('D'); break;
      case 'LEFT' : this.selSetPos('W'); break;
      case 'RIGHT': this.selSetPos('R'); break;
      }
      break;
    case 'R'     :
      switch(direction){
      case 'UP'   : this.selSetPos('FOUR'); break;
      case 'DOWN' : this.selSetPos('F'); break;
      case 'LEFT' : this.selSetPos('E'); break;
      case 'RIGHT': this.selSetPos('T'); break;
      }
      break;
    case 'T'     :
      switch(direction){
      case 'UP'   : this.selSetPos('FIVE'); break;
      case 'DOWN' : this.selSetPos('G'); break;
      case 'LEFT' : this.selSetPos('R'); break;
      case 'RIGHT': this.selSetPos('Y'); break;
      }
      break;
    case 'Y'     :
      switch(direction){
      case 'UP'   : this.selSetPos('SIX'); break;
      case 'DOWN' : this.selSetPos('H'); break;
      case 'LEFT' : this.selSetPos('T'); break;
      case 'RIGHT': this.selSetPos('U'); break;
      }
      break;
    case 'U'     :
      switch(direction){
      case 'UP'   : this.selSetPos('SEVEN'); break;
      case 'DOWN' : this.selSetPos('J'); break;
      case 'LEFT' : this.selSetPos('Y'); break;
      case 'RIGHT': this.selSetPos('I'); break;
      }
      break;
    case 'I'     :
      switch(direction){
      case 'UP'   : this.selSetPos('EIGHT'); break;
      case 'DOWN' : this.selSetPos('K'); break;
      case 'LEFT' : this.selSetPos('U'); break;
      case 'RIGHT': this.selSetPos('O'); break;
      }
      break;
    case 'O'     :
      switch(direction){
      case 'UP'   : this.selSetPos('NINE'); break;
      case 'DOWN' : this.selSetPos('L'); break;
      case 'LEFT' : this.selSetPos('I'); break;
      case 'RIGHT': this.selSetPos('P'); break;
      }
      break;
    case 'P'     :
      switch(direction){
      case 'UP'   : this.selSetPos('ZERO'); break;
      case 'DOWN' : this.selSetPos('COLON'); break;
      case 'LEFT' : this.selSetPos('O'); break;
      case 'RIGHT': this.selSetPos('BRKTL'); break;
      }
      break;
    case 'BRKTL' :
      switch(direction){
      case 'UP'   : this.selSetPos('MINUS'); break;
      case 'DOWN' : this.selSetPos('QUOTE'); break;
      case 'LEFT' : this.selSetPos('P'); break;
      case 'RIGHT': this.selSetPos('BRKTR'); break;
      }
      break;
    case 'BRKTR' :
      switch(direction){
      case 'UP'   : this.selSetPos('EQUAL'); break;
      case 'DOWN' : this.selSetPos('ENTER'); break;
      case 'LEFT' : this.selSetPos('BRKTL'); break;
      case 'RIGHT': this.selSetPos('PIPE'); break;
      }
      break;
    case 'PIPE'  :
      switch(direction){
      case 'UP'   : this.selSetPos('BACK'); break;
      case 'DOWN' : this.selSetPos('ENTER'); break;
      case 'LEFT' : this.selSetPos('BRKTR'); break;
      case 'RIGHT': break;
      }
      break;

    case 'A'     :
      switch(direction){
      case 'UP'   : this.selSetPos('Q'); break;
      case 'DOWN' : this.selSetPos('Z'); break;
      case 'LEFT' : break;
      case 'RIGHT': this.selSetPos('S'); break;
      }
      break;
    case 'S'     :
      switch(direction){
      case 'UP'   : this.selSetPos('W'); break;
      case 'DOWN' : this.selSetPos('X'); break;
      case 'LEFT' : this.selSetPos('A'); break;
      case 'RIGHT': this.selSetPos('D'); break;
      }
      break;
    case 'D'     :
      switch(direction){
      case 'UP'   : this.selSetPos('E'); break;
      case 'DOWN' : this.selSetPos('C'); break;
      case 'LEFT' : this.selSetPos('S'); break;
      case 'RIGHT': this.selSetPos('F'); break;
      }
      break;
    case 'F'     :
      switch(direction){
      case 'UP'   : this.selSetPos('R'); break;
      case 'DOWN' : this.selSetPos('V'); break;
      case 'LEFT' : this.selSetPos('D'); break;
      case 'RIGHT': this.selSetPos('G'); break;
      }
      break;
    case 'G'     :
      switch(direction){
      case 'UP'   : this.selSetPos('T'); break;
      case 'DOWN' : this.selSetPos('B'); break;
      case 'LEFT' : this.selSetPos('F'); break;
      case 'RIGHT': this.selSetPos('H'); break;
      }
      break;
    case 'H'     :
      switch(direction){
      case 'UP'   : this.selSetPos('Y'); break;
      case 'DOWN' : this.selSetPos('N'); break;
      case 'LEFT' : this.selSetPos('G'); break;
      case 'RIGHT': this.selSetPos('J'); break;
      }
      break;
    case 'J'     :
      switch(direction){
      case 'UP'   : this.selSetPos('U'); break;
      case 'DOWN' : this.selSetPos('M'); break;
      case 'LEFT' : this.selSetPos('H'); break;
      case 'RIGHT': this.selSetPos('K'); break;
      }
      break;
    case 'K'     :
      switch(direction){
      case 'UP'   : this.selSetPos('I'); break;
      case 'DOWN' : this.selSetPos('COMMA'); break;
      case 'LEFT' : this.selSetPos('J'); break;
      case 'RIGHT': this.selSetPos('L'); break;
      }
      break;
    case 'L'     :
      switch(direction){
      case 'UP'   : this.selSetPos('O'); break;
      case 'DOWN' : this.selSetPos('POINT'); break;
      case 'LEFT' : this.selSetPos('K'); break;
      case 'RIGHT': this.selSetPos('COLON'); break;
      }
      break;
    case 'COLON' :
      switch(direction){
      case 'UP'   : this.selSetPos('P'); break;
      case 'DOWN' : this.selSetPos('SLASH'); break;
      case 'LEFT' : this.selSetPos('L'); break;
      case 'RIGHT': this.selSetPos('QUOTE'); break;
      }
      break;
    case 'QUOTE' :
      switch(direction){
      case 'UP'   : this.selSetPos('BRKTL'); break;
      case 'DOWN' : this.selSetPos('SPACE'); break;
      case 'LEFT' : this.selSetPos('COLON'); break;
      case 'RIGHT': this.selSetPos('ENTER'); break;
      }
      break;
    case 'ENTER' :
      switch(direction){
      case 'UP'   : this.selSetPos('PIPE'); break;
      case 'DOWN' : this.selSetPos('SPACE'); break;
      case 'LEFT' : this.selSetPos('QUOTE'); break;
      case 'RIGHT': break;
      }
      break;

    case 'SHIFT' :
      switch(direction){
      case 'UP'   : this.selSetPos('GRAVE'); break;
      case 'DOWN' : break;
      case 'LEFT' : break;
      case 'RIGHT': this.selSetPos('Z'); break;
      }
      break;
    case 'Z'     :
      switch(direction){
      case 'UP'   : this.selSetPos('A'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('SHIFT'); break;
      case 'RIGHT': this.selSetPos('X'); break;
      }
      break;
    case 'X'     :
      switch(direction){
      case 'UP'   : this.selSetPos('S'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('Z'); break;
      case 'RIGHT': this.selSetPos('C'); break;
      }
      break;
    case 'C'     :
      switch(direction){
      case 'UP'   : this.selSetPos('D'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('X'); break;
      case 'RIGHT': this.selSetPos('V'); break;
      }
      break;
    case 'V'     :
      switch(direction){
      case 'UP'   : this.selSetPos('F'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('C'); break;
      case 'RIGHT': this.selSetPos('B'); break;
      }
      break;
    case 'B'     :
      switch(direction){
      case 'UP'   : this.selSetPos('G'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('V'); break;
      case 'RIGHT': this.selSetPos('N'); break;
      }
      break;
    case 'N'     :
      switch(direction){
      case 'UP'   : this.selSetPos('H'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('B'); break;
      case 'RIGHT': this.selSetPos('M'); break;
      }
      break;
    case 'M'     :
      switch(direction){
      case 'UP'   : this.selSetPos('J'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('N'); break;
      case 'RIGHT': this.selSetPos('COMMA'); break;
      }
      break;
    case 'COMMA' :
      switch(direction){
      case 'UP'   : this.selSetPos('K'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('M'); break;
      case 'RIGHT': this.selSetPos('POINT'); break;
      }
      break;
    case 'POINT' :
      switch(direction){
      case 'UP'   : this.selSetPos('L'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('COMMA'); break;
      case 'RIGHT': this.selSetPos('SLASH'); break;
      }
      break;
    case 'SLASH' :
      switch(direction){
      case 'UP'   : this.selSetPos('COLON'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('POINT'); break;
      case 'RIGHT': this.selSetPos('SPACE'); break;
      }
      break;
    case 'SPACE' :
      switch(direction){
      case 'UP'   : this.selSetPos('ENTER'); break;
      case 'DOWN' : break;
      case 'LEFT' : this.selSetPos('SLASH'); break;
      case 'RIGHT': break;
      }
      break;
    }
  };
  this.padInput = function(){
    var ret = false;
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padUP)){
      this.selMove('UP');
    }
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padDOWN)){
      this.selMove('DOWN');
    }
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padLEFT)){
      this.selMove('LEFT');
    }
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padRIGHT)){
      this.selMove('RIGHT');
    }
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padOK)){
      ret = this.currentSelPos;
    }
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padCancel)){
      ret = 'BACK';
    }
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padOption1)){
      ret = 'OPTION1';
    }
    if (game.input.gamepad.pad1.justPressed(RGinput.menu.padOption2)){
      ret = 'OPTION2';
    }
    if(ret!==false){
      this.inputMode = 'gamepad';
      switch(ret){
      case 'ESC':
        break;
      case 'SHIFT':
        if(this.isShiftOn){
          this.img.frame=0;
          this.isShiftOn=false;
        }
        else {
          this.img.frame=1;
          this.isShiftOn=true;
        }
        break;
      case 'BACK':
        break;
      case 'ENTER':
        break;
      case 'SPACE':
        break;
      }
      this.stringPush(ret);
    }
    return ret;
  };
  this.keyInput = function(){
    var ret = false;
    if(game.input.keyboard.isDown(Phaser.Keyboard.SHIFT)){
      this.inputMode = 'keyboard';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.ONE  )) ret = '!';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.TWO  )) ret = '@';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.THREE)) ret = '#';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.FOUR )) ret = '$';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.FIVE )) ret = '%'; 
      if(game.input.keyboard.justPressed(Phaser.Keyboard.SIX  )) ret = '^';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.SEVEN)) ret = '&';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.EIGHT)) ret = '*';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.NINE )) ret = '(';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.ZERO )) ret = ')';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.Q    )) ret = 'Q';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.W    )) ret = 'W';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.E    )) ret = 'E';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.R    )) ret = 'R';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.T    )) ret = 'T';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.Y    )) ret = 'Y';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.U    )) ret = 'U';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.I    )) ret = 'I';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.O    )) ret = 'O';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.P    )) ret = 'P';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.A    )) ret = 'A';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.S    )) ret = 'S';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.D    )) ret = 'D';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.F    )) ret = 'F';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.G    )) ret = 'G';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.H    )) ret = 'H';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.J    )) ret = 'J';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.K    )) ret = 'K';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.L    )) ret = 'L';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.Z    )) ret = 'Z';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.X    )) ret = 'X';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.C    )) ret = 'C';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.V    )) ret = 'V';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.B    )) ret = 'B';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.N    )) ret = 'N';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.M    )) ret = 'M';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.COLON)) ret = ':';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.EQUALS)) ret = '+';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.COMMA)) ret = '<';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.PERIOD)) ret = '>';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.UNDERSCORE)) ret = '_';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.QUESTION_MARK)) ret = '?';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.TILDE)) ret = '~';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.OPEN_BRACKET)) ret = '{';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.CLOSED_BRACKET)) ret = '}';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.BACKWARD_SLASH)) ret = '|';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.QUOTES)) ret = '"';
    }
    else {
      if(game.input.keyboard.justPressed(Phaser.Keyboard.ONE  )) ret = '1';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.TWO  )) ret = '2';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.THREE)) ret = '3';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.FOUR )) ret = '4';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.FIVE )) ret = '5'; 
      if(game.input.keyboard.justPressed(Phaser.Keyboard.SIX  )) ret = '6';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.SEVEN)) ret = '7';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.EIGHT)) ret = '8';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.NINE )) ret = '9';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.ZERO )) ret = '0';

      if(game.input.keyboard.justPressed(Phaser.Keyboard.Q    )) ret = 'q';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.W    )) ret = 'w';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.E    )) ret = 'e';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.R    )) ret = 'r';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.T    )) ret = 't';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.Y    )) ret = 'y';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.U    )) ret = 'u';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.I    )) ret = 'i';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.O    )) ret = 'o';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.P    )) ret = 'p';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.A    )) ret = 'a';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.S    )) ret = 's';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.D    )) ret = 'd';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.F    )) ret = 'f';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.G    )) ret = 'g';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.H    )) ret = 'h';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.J    )) ret = 'j';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.K    )) ret = 'k';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.L    )) ret = 'l';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.Z    )) ret = 'z';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.X    )) ret = 'x';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.C    )) ret = 'c';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.V    )) ret = 'v';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.B    )) ret = 'b';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.N    )) ret = 'n';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.M    )) ret = 'm';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.COLON)) ret = ';';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.EQUALS)) ret = '=';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.COMMA)) ret = ',';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.PERIOD)) ret = '.';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.UNDERSCORE)) ret = '-';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.QUESTION_MARK)) ret = '/';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.TILDE)) ret = '`';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.OPEN_BRACKET)) ret = '[';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.CLOSED_BRACKET)) ret = ']';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.BACKWARD_SLASH)) ret = '\\';
      if(game.input.keyboard.justPressed(Phaser.Keyboard.QUOTES)) ret = "'";
      if(game.input.keyboard.justPressed(Phaser.Keyboard.BACKSPACE)) ret = "BACK";
      if(game.input.keyboard.justPressed(Phaser.Keyboard.ESC)) ret = "ESC";
      if(game.input.keyboard.justPressed(Phaser.Keyboard.ENTER)) ret = "ENTER";
      if(game.input.keyboard.justPressed(Phaser.Keyboard.SPACEBAR)) ret = "SPACE";
    }
    if(ret!==false){
      this.inputMode = 'keyboard';
      this.stringPush(ret);
    }
    if(this.inputMode == 'keyboard'){
      if(game.input.keyboard.isDown(Phaser.Keyboard.ONE  )) 
        this.ONE.button.frame=1;
      else 
        this.ONE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.TWO  )) 
        this.TWO.button.frame=1;
      else 
        this.TWO.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.THREE)) 
        this.THREE.button.frame=1;
      else 
        this.THREE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.FOUR )) 
        this.FOUR.button.frame=1;
      else 
        this.FOUR.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.FIVE ))  
        this.FIVE.button.frame=1;
      else 
        this.FIVE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.SIX  )) 
        this.SIX.button.frame=1;
      else 
        this.SIX.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.SEVEN)) 
        this.SEVEN.button.frame=1;
      else 
        this.SEVEN.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.EIGHT)) 
        this.EIGHT.button.frame=1;
      else 
        this.EIGHT.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.NINE )) 
        this.NINE.button.frame=1;
      else 
        this.NINE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.ZERO )) 
        this.ZERO.button.frame=1;
      else 
        this.ZERO.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.Q    )) 
        this.Q.button.frame=1;
      else 
        this.Q.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.W    )) 
        this.W.button.frame=1;
      else 
        this.W.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.E    )) 
        this.E.button.frame=1;
      else 
        this.E.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.R    )) 
        this.R.button.frame=1;
      else 
        this.R.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.T    )) 
        this.T.button.frame=1;
      else 
        this.T.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.Y    )) 
        this.Y.button.frame=1;
      else 
        this.Y.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.U    )) 
        this.U.button.frame=1;
      else 
        this.U.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.I    )) 
        this.I.button.frame=1;
      else 
        this.I.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.O    )) 
        this.O.button.frame=1;
      else 
        this.O.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.P    )) 
        this.P.button.frame=1;
      else 
        this.P.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.A    )) 
        this.A.button.frame=1;
      else 
        this.A.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.S    )) 
        this.S.button.frame=1;
      else 
        this.S.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.D    )) 
        this.D.button.frame=1;
      else 
        this.D.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.F    )) 
        this.F.button.frame=1;
      else 
        this.F.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.G    )) 
        this.G.button.frame=1;
      else 
        this.G.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.H    )) 
        this.H.button.frame=1;
      else 
        this.H.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.J    )) 
        this.J.button.frame=1;
      else 
        this.J.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.K    )) 
        this.K.button.frame=1;
      else 
        this.K.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.L    )) 
        this.L.button.frame=1;
      else 
        this.L.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.Z    )) 
        this.Z.button.frame=1;
      else 
        this.Z.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.X    )) 
        this.X.button.frame=1;
      else 
        this.X.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.C    )) 
        this.C.button.frame=1;
      else 
        this.C.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.V    )) 
        this.V.button.frame=1;
      else 
        this.V.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.B    )) 
        this.B.button.frame=1;
      else 
        this.B.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.N    )) 
        this.N.button.frame=1;
      else 
        this.N.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.M    )) 
        this.M.button.frame=1;
      else 
        this.M.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.COLON)) 
        this.COLON.button.frame=1;
      else 
        this.COLON.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.EQUALS)) 
        this.EQUAL.button.frame=1;
      else 
        this.EQUAL.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.COMMA)) 
        this.COMMA.button.frame=1;
      else 
        this.COMMA.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.PERIOD)) 
        this.POINT.button.frame=1;
      else 
        this.POINT.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.UNDERSCORE)) 
        this.MINUS.button.frame=1;
      else 
        this.MINUS.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.QUESTION_MARK)) 
        this.SLASH.button.frame=1;
      else 
        this.SLASH.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.TILDE)) 
        this.GRAVE.button.frame=1;
      else 
        this.GRAVE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.OPEN_BRACKET)) 
        this.BRKTL.button.frame=1;
      else 
        this.BRKTL.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.CLOSED_BRACKET)) 
        this.BRKTR.button.frame=1;
      else 
        this.BRKTR.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.BACKWARD_SLASH)) 
        this.PIPE.button.frame=1;
      else 
        this.PIPE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.QUOTES)) 
        this.QUOTE.button.frame=1;
      else 
        this.QUOTE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.BACKSPACE)) 
        this.BACK.button.frame=1;
      else 
        this.BACK.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.ESC)) 
        this.ESC.button.frame=1;
      else 
        this.ESC.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.ENTER)) 
        this.ENTER.button.frame=1;
      else 
        this.ENTER.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.SPACEBAR)) 
        this.SPACE.button.frame=1;
      else 
        this.SPACE.button.frame=0;
      if(game.input.keyboard.isDown(Phaser.Keyboard.SHIFT)){
        this.img.frame=1;
        this.isShiftOn=true;
      }
      else{
        this.img.frame=0;
        this.isShiftOn=false;
      }
    }
    return ret;
  };
};

var VkeyPos = {
  ESC   : {x:   0, y:   0, w: 20, n: 'ESC'},
  ONE   : {x:  20, y:   0, w: 20, n: 'ONE'},
  TWO   : {x:  40, y:   0, w: 20, n: 'TWO'},
  THREE : {x:  60, y:   0, w: 20, n: 'THREE'},
  FOUR  : {x:  80, y:   0, w: 20, n: 'FOUR'},
  FIVE  : {x: 100, y:   0, w: 20, n: 'FIVE'},
  SIX   : {x: 120, y:   0, w: 20, n: 'SIX'},
  SEVEN : {x: 140, y:   0, w: 20, n: 'SEVEN'},
  EIGHT : {x: 160, y:   0, w: 20, n: 'EIGHT'},
  NINE  : {x: 180, y:   0, w: 20, n: 'NINE'},
  ZERO  : {x: 200, y:   0, w: 20, n: 'ZERO'},
  MINUS : {x: 220, y:   0, w: 20, n: 'MINUS'},
  EQUAL : {x: 240, y:   0, w: 20, n: 'EQUAL'},
  BACK  : {x: 260, y:   0, w: 40, n: 'BACK'},

  GRAVE : {x:   0, y:  20, w: 30, n: 'GRAVE'},
  Q     : {x:  30, y:  20, w: 20, n: 'Q'},
  W     : {x:  50, y:  20, w: 20, n: 'W'},
  E     : {x:  70, y:  20, w: 20, n: 'E'},
  R     : {x:  90, y:  20, w: 20, n: 'R'},
  T     : {x: 110, y:  20, w: 20, n: 'T'},
  Y     : {x: 130, y:  20, w: 20, n: 'Y'},
  U     : {x: 150, y:  20, w: 20, n: 'U'},
  I     : {x: 170, y:  20, w: 20, n: 'I'},
  O     : {x: 190, y:  20, w: 20, n: 'O'},
  P     : {x: 210, y:  20, w: 20, n: 'P'},
  BRKTL : {x: 230, y:  20, w: 20, n: 'BRKTL'},
  BRKTR : {x: 250, y:  20, w: 20, n: 'BRKTR'},
  PIPE  : {x: 270, y:  20, w: 30, n: 'PIPE'},

  CAPS  : {x:   0, y:  40, w: 40, n: 'CAPS'},
  A     : {x:  40, y:  40, w: 20, n: 'A'},
  S     : {x:  60, y:  40, w: 20, n: 'S'},
  D     : {x:  80, y:  40, w: 20, n: 'D'},
  F     : {x: 100, y:  40, w: 20, n: 'F'},
  G     : {x: 120, y:  40, w: 20, n: 'G'},
  H     : {x: 140, y:  40, w: 20, n: 'H'},
  J     : {x: 160, y:  40, w: 20, n: 'J'},
  K     : {x: 180, y:  40, w: 20, n: 'K'},
  L     : {x: 200, y:  40, w: 20, n: 'L'},
  COLON : {x: 220, y:  40, w: 20, n: 'COLON'},
  QUOTE : {x: 240, y:  40, w: 20, n: 'QUOTE'},
  ENTER : {x: 260, y:  40, w: 40, n: 'ENTER'},

  SHIFT : {x:   0, y:  60, w: 50, n: 'SHIFT'},
  Z     : {x:  50, y:  60, w: 20, n: 'Z'},
  X     : {x:  70, y:  60, w: 20, n: 'X'},
  C     : {x:  90, y:  60, w: 20, n: 'C'},
  V     : {x: 110, y:  60, w: 20, n: 'V'},
  B     : {x: 130, y:  60, w: 20, n: 'B'},
  N     : {x: 150, y:  60, w: 20, n: 'N'},
  M     : {x: 170, y:  60, w: 20, n: 'M'},
  COMMA : {x: 190, y:  60, w: 20, n: 'COMMA'},
  POINT : {x: 210, y:  60, w: 20, n: 'POINT'},
  SLASH : {x: 230, y:  60, w: 20, n: 'SLASH'},
  SPACE : {x: 250, y:  60, w: 50, n: 'SPACE'}
};