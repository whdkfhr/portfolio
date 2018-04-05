var game = new Phaser.Game(320, 180, Phaser.AUTO, 'chiprg');

// DECLARE GAME STATES
game.state.add('screenInit', screenInit);
game.state.add('screenStart', screenStart);
game.state.add('screenSelectAccount', screenSelectAccount);
game.state.add('screenLogin', screenLogin);
game.state.add('screenLobby', screenLobby);
game.state.add('screenConfig', screenConfig);
game.state.add('screenRanking', screenRanking);
game.state.add('screenFreePlayInit', screenFreePlayInit);
game.state.add('screenFreePlay', screenFreePlay);
game.state.add('screenCoursePlayInit', screenCoursePlayInit);
game.state.add('screenCoursePlay', screenCoursePlay);
game.state.add('screenPlayInit', screenPlayInit);
game.state.add('screenPlay', screenPlay);
game.state.add('screenResult', screenResult);
game.state.add('screenCourseInit', screenCourseInit);
game.state.add('screenPlayEntryInit', screenPlayEntryInit);
game.state.add('screenEntryResult', screenEntryResult);
game.state.add('screenCourseResult', screenCourseResult);

game.state.start('screenInit');
