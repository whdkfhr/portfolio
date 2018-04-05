
// require
var query = require('../query.js');

// const
var DBPATH = "mongodb://studio2aoe:t1emppa47ssw883ord@localhost:27017/chiprg";

module.exports = function(app)
{
  app.get('/',function(req,res){
    res.send('game/index.html');
  });

  app.get('/user',function(req,res){
    query.connectDB(DBPATH).
      then(function(resolve){
        return query.getUser(
          resolve, req.params.userID);
      }).
      then(function(resolve){
        res.send(resolve);
      });
  });

  app.get('/freeranking', function(req, res){
    console.log(req.query);
    query.connectDB(DBPATH).
      then(function(resolve){
        return query.getFreeRanking(
          resolve, req.query.stageID, req.query.userID, req.query.limit);
      }).
      then(function(resolve){
        res.send(resolve);
      });
  });

  app.post('/freeranking', function(req, res){
    query.connectDB(DBPATH).
      then(function(resolve){
        return query.postFreeRanking(resolve, req.body);
      }).
      then(function(resolve){
        res.send(resolve);
      });
  });
  
  app.get('/courseranking', function(req, res){
    console.log(req.query);
    query.connectDB(DBPATH).
      then(function(resolve){
        return query.getCourseRanking(
          resolve, req.params.courseID, req.params.userID, req.params.limit);
      }).
      then(function(resolve){
        res.send(resolve);
      });
  });

  app.post('/courseranking', function(req, res){
    query.connectDB(DBPATH).
      then(function(resolve){
        return query.postCourseRanking(resolve, req.body);
      }).
      then(function(resolve){
        res.send(resolve);
      });
  });
};