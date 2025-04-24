'use strict';

const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const schema = new Schema({
    name: {
        type: String,
        required: true
    },
    cpf: {
        type: String,
        required: true,
    },
    email: {
        type: String,
        required: true
    },
    password: {
        type: String,
        required: true
    },
    phones: [
        {
            type: String,
        }
    ],
    address: {
        cep: {
            type: String,
            required: true
        },
        city: {
            type: String,
            required: true
        },
        state: {
            type: String,
            required: true
        },
        neighbourhood: {
            type: String,
            required: true
        },
        street: {
            type: String,
            required: true
        },
        number: {
            type: Number,
            required: true
        },
        complement: {
            type: String,
            default: ""
        },
        additional: {
            type: String,
            default: ""
        },
    },
    admin: {
        type: Boolean,
        required: true
    },
    cart: [{
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
        product: {
            type: mongoose.Schema.Types.ObjectId,
            ref: 'Product'
        }
    }]
});

module.exports = mongoose.model('User', schema);