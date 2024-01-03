document.querySelector('.next').onclick = function(){
    if( window.location.pathname == "/index.html"){
        window.location.pathname = "/pictures.html";
    }
    if( window.location.pathname == "/pictures.html"){
        window.location.pathname = "/videos.html";
    }
    if( window.location.pathname == "/videos.html"){
        window.location.pathname = "/history.html";
    }
}
document.querySelector('.prev').onclick = function(){
    if( window.location.pathname == "/history.html"){
        window.location.pathname = "/videos.html";
    }
    if( window.location.pathname == "/videos.html"){
        window.location.pathname = "/pictures.html";
    }
    if( window.location.pathname == "/pictures.html"){
        window.location.pathname = "/index.html";
    }
}
