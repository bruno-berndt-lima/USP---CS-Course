'use strict';

const express = require('express');
const router = express.Router();
const controller = require('../controllers/login-controller');

router.post('/', controller.login);
router.get('/:email', controller.getByEmail);

module.exports = router;