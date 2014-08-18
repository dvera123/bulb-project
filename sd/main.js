

$(document).ready(function() {


	if (annyang) {

		var on = function() {
	      $.ajax({
			  type: 'GET',	
			  data: { do: "on"}
			}).done(function(content) {
				$('body').addClass('night');
				console.log("on");
			});
	      
	    };

	    var off = function() {
	      $.ajax({
			  type: 'GET',	
			  data: { do: "off"}
			}).done(function(content) {
				$('body').removeClass('night');
				console.log("off");
			});
	      
	    };

		var commands = {
	     'on': on,
	     'off': off
	    };

	    
	    annyang.init(commands);
	    annyang.start();
	}	

	$('body').on('click', function(){
		if($(this).hasClass('night')){
			$.ajax({
			  type: 'GET',	
			  data: { do: "off"}
			}).done(function(content) {
				$('body').removeClass('night');
				console.log("off");
			});
		}

		else{
			$.ajax({
			  type: 'GET',	
			  data: { do: "on"}
			}).done(function(content) {
				$('body').addClass('night');
				console.log("on");
			});
		}
	});

});

