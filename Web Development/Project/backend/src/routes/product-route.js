'use strict';

const express = require('express');
const router = express.Router();
const controller = require('../controllers/product-controller');

router.get('/', controller.getPage);
router.get('/admin', controller.get);
router.get('/product', controller.getRelated);
router.get('/:slug', controller.getBySlug);
router.get('/admin/:id', controller.getByID);
router.post('/', controller.post);
router.put('/:id', controller.put);
router.delete('/', controller.delete);

module.exports = router;