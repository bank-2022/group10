var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const helmet = require('helmet');
const cors = require('cors');

var indexRouter = require('./routes/index');
// var usersRouter = require('./routes/users');
var asiakasRouter = require('./routes/asiakas');
var tiliRouter = require('./routes/tili')


var app = express();


app.use(helmet());
app.use(cors());
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
// app.use('/users', usersRouter);
app.use('/asiakas', asiakasRouter);
app.use('/tili', tiliRouter)


module.exports = app;
