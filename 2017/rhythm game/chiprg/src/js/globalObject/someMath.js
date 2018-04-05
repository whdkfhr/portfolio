var SomeMath = {
  modulo: function(a, b){
    if(a<0) a=b+a;
    return a % b;
  },
  pad0: function(n, width, z) {
    z = z || '0';
    n = n + '';
    return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
  }
};