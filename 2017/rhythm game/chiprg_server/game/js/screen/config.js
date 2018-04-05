var screenConfig = {
  name: "screenConfig",
  title: "",
  preload: function(){
  },
  create: function(){
    this.title = game.add.text(0, 0, this.name, { font: "14px Arial", fill: "#ffffff"});
  },
};
