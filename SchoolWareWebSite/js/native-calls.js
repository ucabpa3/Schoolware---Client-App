//alert(test.returnStr());
//alert(test.returnInt());
//test.passInt(2);
//test.passStr("Hello again.");
$("#gen-content a").click(function(){
       event.preventDefault();
       linker.initiateDownload($(this).attr('href'));
       //var appPath = $(this).attr('href');
       //var exit = linker.launchJar(appPath);
       //if(exit == 1){
        //alert("Make sure you have the application installed in the path:"+appPath);
        //}

       	});

