var express = require('express');
var router = express.Router();
var mongoose = require( 'mongoose' );
var User = mongoose.model('User');
var bcrypt = require('bcrypt');

const saltRounds = 10;

var success_response = {
	state: 'success',
	user: {username : undefined}
};
var wrong_password_response = {
	state: 'failure',
	msg: 'Incorrect user or password'
};
var no_users_response = {
	state: 'failure',
	msg: 'Currently we have no users in database. Please register first.'
};


	router.route('/login').post(function(req, res){
		var user_data = req.body;
		var authenticated = false;
		var userInDatabase = false;

		User.find(function(err, users){
			users.forEach(function(user){
				if(user.username == user_data.username){
					userInDatabase = true;
					bcrypt.compare(user_data.password, user.password, function(err, doesMatch) {
						if(doesMatch){
							success_response.user.username = user.username
							res.send(success_response);
						} else {
							res.send(wrong_password_response);
						}
					});
				}
			});

			if(users.length == 0){ // no users in database
				res.send(no_users_response);
			} else if (!userInDatabase){
				res.send(wrong_password_response);
			}
		});
	});

	router.route('/register').post(function(req, res){
		var user_data = req.body;
		user = new User();
		user.username = user_data.username;
		bcrypt.hash(user_data.password, saltRounds, function(error, hash) {
			if(!error){
				user.password = hash;
				user.save(function(err, hash) {
						if(err){
							console.log("Error: " + error);
						}
				});
				return true;
			} else {
				console.log("Error: " + error);
				return false;
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
