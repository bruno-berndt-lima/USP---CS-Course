'use strict';

// Need to install npm http, npm debug, npm express, npm bodyParser
// Optional: npm install nodemon --save-dev
const http = require('http');
const debug = require('debug')('nodestr:server');
const express = require('express');
const bodyParser = require('body-parser');

// Array of posts
let posts = [
    {
        id: 1,
        title: "Primeiro post",
        content: "Esse eh o nosso primeiro post adicionado",
        author: "Vscode"
    },
    {
        id: 2,
        title: "Primeiro post",
        content: "Esse eh o nosso primeiro post adicionado",
        author: "Vscode"
    },
    {
        id: 3,
        title: "Primeiro post",
        content: "Esse eh o nosso primeiro post adicionado",
        author: "Vscode"
    }
]
let currentId = posts.length;

// Create an Express application
const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));


// Set the port for the application
const port = normalizePort(process.env.PORT || '3000');
app.set('port', port);

// Create an HTTP server
const server = http.createServer(app);
const router = express.Router();

//Middleware function to log request protocol
app.use('/posts', function(req, res, next){
    let date = new Date();
    let day = date.getDate();
    let month = date.getMonth();
    let year = date.getFullYear();
    let hour = date.getHours();
    let minutes = date.getMinutes();
    let seconds = date.getSeconds();
    let milisseconds = date.getMilliseconds();
    let string = day + "/" + month + "/" + year + " " + hour + ":" + minutes + ":" + seconds + "." + milisseconds;

    console.log("A request for things received at " + string);
    next();
 });

// GET request to retrieve all posts
const get = router.get('/', (req, res, next) => {
    res.status(200).send(
        posts
    );
});

// GET request to retrieve a specific post by ID
const getID = router.get('/:id', (req, res, next) => {
    // Filtering the post with the ID specified in the URL
    const answer = posts.filter(post => {
        if (post.id == req.params.id) return post;
    })[0]

    res.status(200).send(
        answer
    );
});

// POST request to create a new post
const create = router.post('/', (req, res, next) => {
    res.status(201).send(req.body);
    // Creating a new post with a global variable of id, and the body of requisition
    const post = {
        id: ++currentId,
        title: req.body.title,
        content: req.body.content,
        author: req.body.author
    }
    posts.push(post);
});

// PUT request to update a specific post by ID
const put = router.put('/:id', (req, res, next) => {
    // ID specifiend in the URL
    const id = req.params.id;
    // Updating the value of specified post with the requisition body
    posts = posts.map(post => {
        if (post.id == id) {
            post.title = req.body.title;
            post.author = req.body.author;
            post.content = req.body.content;
        }
        return post;
    })
    res.status(201).send({ id: id, item: req.body });
});

// DELETE request to delete a specific post by ID
const del = router.delete('/:id', (req, res, next) => {
    const id = req.params.id;
    // Filtering posts to remove post with the same id of url
    posts = posts.filter(post => {
        if (post.id != id) return post;
    })
    res.status(200).send(`Post ${id} deletado`);
});

// Specify the routes for different operations
app.use('/posts', get);
app.use('/posts', getID);
app.use('/posts', create);
app.use('/posts', del);
app.use('/posts', put)

// Start the server
server.listen(port);
server.on('error', onError);
server.on('listening', onListening);
console.log('API esta rodando na porta ' + port);

// Helper function to normalize the port value
function normalizePort(val) {
    const port = parseInt(val, 10);

    if (isNaN(port)) {
        return val;
    }

    if (port > 0) {
        return port;
    }

    return false;
}

// Error handler function for the server
function onError(error) {
    if (error.syscall != 'listen') {
        throw error;
    }

    const bind = typeof port === 'string' ?
        'Pipe' + port :
        'Port ' + port;

    switch (error.code) {
        case 'EACCES':
            console.error(bind + ' is already in use');
            process.exit(1);
            break;
        case 'EADDRINUSE':
            console.error(bind + ' is already in use');
            process.exit(1);
            break;
        default:
            throw error;
    }
}

// Function to handle the "listening" event of the server
function onListening() {
    const addr = server.address();
    const bind = typeof addr === 'string' ?
        'Pipe' + addr :
        'Port ' + addr.port;
    debug('Listening on ' + bind)
}
