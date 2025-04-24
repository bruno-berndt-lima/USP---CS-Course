'use strict';

const mongoose = require('mongoose');
const Order = mongoose.model('Order');
 
exports.get = () => {
    return Order.find({})
        .populate('user')
        .populate('items.product');
}

exports.create = data => {
    const order = new Order(data);
    return order.save();
}