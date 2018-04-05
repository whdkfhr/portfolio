var SomeMath = {
  modulo: function(a, b){
    if(a<0) a=b+a;
    return a % b;
  },
  pad0: function(n, width, z) {
    z = z || '0';
    n = n + '';
    return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
  },
  paddRight: function(string, n, char) {
    if(string.length >= n) return string.slice(0, n);
    else{
      var repeat = n-string.length;
      for(var i=0; i<repeat; i++){
        string += char;
      }
      return string;
    }
  }
};