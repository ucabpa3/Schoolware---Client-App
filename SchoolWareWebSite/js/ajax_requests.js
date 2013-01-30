function retrieveCategories(){

    $("#loading-wrapper span").text("Loading...");
    $("#loading-wrapper").animate({bottom: "+=70"},200,function(){

        $("#br-cat ul").append('<li id="all"><a onfocus="blur();">All</a></li>');

        $.getJSON("http://schoolware.cs.ucl.ac.uk:9999/aad-ws/api/categories", function(data) {

            $.each(data, function(i, item) {

                $.each(item,function(prop,value){
                    $("#br-cat ul").append('<li id="'+value.categId+'"><a onfocus="blur();">'+value.categType+'</a></li>');
                });

              });

        })
        .success(function(){
            $("#loading-wrapper").animate({bottom: "-=70"},200);}
        )
        .error(function(jq, textstatus, errorThrown) {
            $("#loading-wrapper").animate({bottom: "-=70"},200);
                alert("Error: "+errorThrown);
        });

    });

}

function retrieveAppsByCat(category){

    $("#app-pane").fadeOut("fast",function(){
        $(this).empty();
        $("#loading-wrapper span").text("Loading...");
        $("#loading-wrapper").animate({bottom: "+=70"},200,function(){

            $.getJSON("http://schoolware.cs.ucl.ac.uk:9999/aad-ws/api/applications/2", function(data) {
              $.each(data, function(i,apps) {
                  $.each(apps,function(prop,value){
                      $("#app-pane").append('<div class="browse-app" category="'+value.categoryName+'" description=\"'+value.description+'\"><a href="'+value.url+'" onfocus="blur();"><img src="img/application_icon.png"/>'+value.name+'</a></div>');
                     $(".browse-app").fadeIn("fast");
                  });

                });
            })
            .success(function(){
             $("#loading-wrapper").animate({bottom: "-=70"},200);

             })
            .error(function(jq, textstatus, errorThrown) {
                $("#loading-wrapper").animate({bottom: "-=70"},200);
                alert("Error: "+errorThrown);
            });

     });
        }).fadeIn("fast");
}

function sendTestResults(str){

    var json;

    try{

        json = JSON.parse(str);
        $("#loading-wrapper span").text("Sending resutls...");
        $("#loading-wrapper").animate({bottom: "+=70"},200,function(){

            $.ajax({
                    type: "POST",
                    url: "http://schoolwaretest.co.nf/test3.php",
                       data : {json:json}
                }).done(function(msg ) {
                    alert(msg);
                    $("#loading-wrapper").animate({bottom: "-=70"},200);
                  });

        });
    }
    catch(e){
        alert("Error: Application produced faulty resutls.");
    }

}
