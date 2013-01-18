window.onload = function(e){
        		
        		$("#sidebar nav ul li a").click(function(){
        			$("#sidebar nav ul li.selected").removeClass("selected").addClass("non-selected");
        			$(this).parent().removeClass("non-selected").addClass("selected");
					
        			if($("#categories").css("left") == "0px"){
        				$("#categories").animate({left: "+=210"},200);
        			}
        			else if($(this).attr('href') == "#_faq_"){
        				$("#categories").animate({left: "-=210"},200);
        			}
        		});
        		$("#categories ul li a").click(function(){
        			$("#categories li.selected").removeClass("selected");
        			$(this).parent().addClass("selected");
        		});
        		
        	}
