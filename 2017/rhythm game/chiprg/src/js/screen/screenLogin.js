var screenLogin = {
  name: "screenLobby",
  uiPath: "",
  strings: {},
  text: {},
  vkey: "",
  preload: function(){
    this.uiPath = PATH.uiPath(PATH.uiName) + this.name + '/';
  },
  create: function(){
    this.vkey = new Vkeyboard(10, 90);
  },
  update: function(){
    this.vkey.beaming();
    this.vkey.padInput();
    this.vkey.keyInput();
  },
};