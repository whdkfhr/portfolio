var RGuser = function() {
  this.accountData="";
  this.name="";
  this.config="";

  this.init = function(){
    this.accountData="";
    this.name="";
    this.config="";
  };
  this.load = function(loginQuery){
    var account = this.accountData;
    if(loginQuery.type == "guest"){
      this.accountData = loginQuery;
      this.isLogin = true;
      this.name = "GUEST";
    }
    else if(loginQuery.type == "local"){
      console.log("TODO: local account load");
    }
    else if(loginQuery.type == "online"){
      console.log("TODO: online account load");
    }
    else{
      console.log("TODO: message 'Invalid loginQuery'");
    }
  };
  this.save = function(){
    var account = this.accountData;
    if(account.type == "guest"){
      console.log("TODO: message 'guest account can't save data'");
    }
    else if(account.type == "local"){
      console.log("TODO: local account save");
    }
    else if(account.type == "online"){
      console.log("TODO: online account save");
    }
    else {
      console.log("TODO: message 'no login'");
    }
  };

  // Getter
  this.getAccountData = function(){
    return this.accountData;
  };
  this.getName = function(){
    return this.name;
  };
  this.getConfig = function(){
    return this.config;
  };

  // Setter
  this.setName = function(_name){
    this.name = _name;
  };
  this.setConfig = function(_config){
    this.config = _config;
  };
};

var currentUser = new RGuser();