'use strict';

const cors = require('cors');
const express = require('express');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');

const app = express();
app.use(cors());

// Conecta ao banco
mongoose.connect('mongodb+srv://thiago0708s:X2x0eXxgCy50Qpy8@cluster0.v57bkwv.mongodb.net/digitalFit');

// Carrega os models
const Product = require('./models/product');
const User = require('./models/user');
const Order = require('./models/order');

// Carrega as rotas
const indexRoute = require('./routes/index-route');
const productRoute = require('./routes/product-route');
const userRoute = require('./routes/user-route');
const orderRoute = require('./routes/order-route');
const loginRoute = require('./routes/login-route');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.use('/', indexRoute);
app.use('/products', productRoute);
app.use('/users', userRoute);
app.use('/orders', orderRoute);
app.use('/login', loginRoute);

module.exports = app;