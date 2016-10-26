var express = require('express');
var router = express.Router();
var mongoose = require( 'mongoose' );
var User = mongoose.model('User');

var bcrypt = require('bcrypt');
const saltRounds = 10;
const myPlaintextPassword = 's0/\/\P4$$w0rD';
const someOtherPlaintextPassword = 'not_bacon';


	router.route('/login').post(function(req, res){
		var user_data = req.body;
		var authenticated = false;
		User.find(function(err, users){
			users.forEach(function(user){
				if(user.username == user_data.username){
					bcrypt.compare(myPlaintextPassword, hash, function(err, res) {
    				authenticated = true;
					});
				}
			});
		});

		var res_json = {state: 'failure', user: '', message: ''};
		if(authenticated){
			return res.send({state: 'success', user: {username : user_data.username}});
		} else {
			return res.send({state: 'failure', user: ''});
		}
	});

	router.route('/register').post(function(req, res){
		var user_data = req.body;
		user = new User();
		user.username = user_data.username;
		bcrypt.hash(user_data.password, saltRounds, function(err, hash) {
			if(!err){
				user.password = hash;
				user.save(function(err, post) {
						if(err){
							console.log("Error: " + error);
						}
				}););
			} else {
				return res.send(500, err);
			}
		});
		var res_json = {state: 'failure', user: '', message: ''};
		return res.send({state: 'success', user: {username : user_data.username}});
	});

	router.route('/logout').post(function(req, res) {

	});

	var createHash = function(password){
		return password;
	};

module.exports = router;
