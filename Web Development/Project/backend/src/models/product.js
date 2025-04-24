'use strict';

const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const schema = new Schema({
    brand: {
        type: String,
        required: true,
        trim: true
    },
    model: {
        type: String,
        required: true,
        trim: true
    },
    slug: {
        type: String,
        required: true,
        trim: true,
        index: true,
        unique: true
    },
    sizes: [{
        size: {
            type: Number,
            required: true
        },
        stock: {
            type: Number,
            required: true
        }
    }],
    description: {
        type: String,
        required: true,
        trim: true
    },
    price: {
        type: Number,
        required: true
    },
    active: {
        type: Boolean,
        required: true,
        default: true
    },
    sold: {
        type: Number,
        required: true,
        default: 0
    },
    image: {
        type: String,
        required: true
    }
});

module.exports = mongoose.model('Product', schema);