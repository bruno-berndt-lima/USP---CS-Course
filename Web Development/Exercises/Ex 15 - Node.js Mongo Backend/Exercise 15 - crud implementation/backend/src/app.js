'use strict';

const cors = require('cors');
const express = require('express');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');

const app = express();
app.use(cors());

const url = `mongodb+srv://user:user@cluster0.gk1eixd.mongodb.net/store`;
// Conecta ao banco
mongoose.connect(url);

// Carrega os models
const Product = require('./models/product');

// Carrega as rotas
const productRoute = require('./routes/product-route');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.use('/products', productRoute);

module.exports = app;
