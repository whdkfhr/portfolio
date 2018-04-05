
// CONST
var PORT = process.env.PORT || 21003;


// REQUIRE: npm packages
var express = require('express');
var app = express();
var bodyParser  = require('body-parser');


// CONFIG Middlewares
app.use(express.static('public'));
app.use(express.static('game'));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

var router = require('./router')(app);

// RUN SERVER
var server = app.listen(PORT, function(){
  console.log("Express server has started on port "+PORT);
});