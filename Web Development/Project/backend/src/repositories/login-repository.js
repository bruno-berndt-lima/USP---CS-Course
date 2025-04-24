'use strict';

const mongoose = require('mongoose');
const User = mongoose.model('User');

exports.getEmail = email => {
    return User.find({
        email: email
    }, 'name cpf email phones address admin cart')
        .populate('cart.product');
}

exports.login = data => {
    return User.find({
        email: data.email,
        password: data.password
    }, 'name cpf email phones address admin cart');
}