function stringToBoolean(string){
    switch(string.toLowerCase().trim()){
        case "true": case "yes": case "1": return true;
        case "false": case "no": case "0": case null: return false;
        default: return Boolean(string);
    }
}
const urlParams = new URLSearchParams(window.location.search);
const onlyFirmware = urlParams.get('onlyFirmware');
if (onlyFirmware && stringToBoolean(onlyFirmware)===true){
    _('switch-container').style.display = 'none';
}
function disableAll() {
    document.getElementById("overlay").style.display = "block";
}
function enableAll() {
    document.getElementById("overlay").style.display = "none";
}
function _(el) {
    return document.getElementById(el);
}
function uploadFile() {
    var file = _("file1").files[0];
    // alert(file.name+" | "+file.size+" | "+file.type);
    var formdata = new FormData();
    formdata.append(_("file1").name, file, file.name);
    var ajax = new XMLHttpRequest();
    ajax.upload.addEventListener("progress", progressHandler, false);
    ajax.addEventListener("load", completeHandler, false);
    ajax.addEventListener("loadstart", startHandler, false);
    ajax.addEventListener("error", errorHandler, false);
    ajax.addEventListener("abort", abortHandler, false);
    ajax.open("POST", "/update"); // http://www.developphp.com/video/JavaScript/File-Upload-Progress-Bar-Meter-Tutorial-Ajax-PHP
    //use file_upload_parser.php from above url
    ajax.setRequestHeader('Access-Control-Allow-Headers', '*');
    ajax.setRequestHeader('Access-Control-Allow-Origin', '*');
    ajax.send(formdata);
}
function progressHandler(event) {
    _("loaded_n_total").innerHTML = "Uploaded " + event.loaded + " bytes of " + event.total;
    var percent = Math.round((event.loaded / event.total) * 100);
    _("progressBar").style = 'width: ' + percent + '%';
    _("status").innerHTML = percent + "% uploaded... please wait";
}
function completeHandler(event) {
    enableAll();
    if (event.target.responseText.indexOf('error')>=0){
        _("status").innerHTML = event.target.responseText;
    }else {
        _("status").innerHTML = 'Upload Success!'; //event.target.responseText;
    }
    _("progressBar").value = 0; //wil clear progress bar after successful upload
}
function startHandler(event) {
    disableAll();
}
function errorHandler(event) {
    enableAll();
    _("status").innerHTML = "Upload Failed";
}
function abortHandler(event) {
    enableAll();
    _("status").innerHTML = "Upload Aborted";
}
_('upload_form').addEventListener('submit', (e) => {
    e.preventDefault();
    uploadFile();
});
_('firmware-button').addEventListener('click',
    function (e) {
        e.target.classList.add('selected');
        _('filesystem-button').classList.remove('selected');
        _("file1").name = 'firmware';
    }
)
_('filesystem-button').addEventListener('click',
    function (e) {
        e.target.classList.add('selected');
        _('firmware-button').classList.remove('selected');
        _("file1").name = 'filesystem';
    }
)
_('file1').addEventListener('change', function(e){
    var file = _("file1").files[0];
    if (file && file.name){
        _('button-send').disabled = false;
    }else{
        _('button-send').disabled = true;
    }
    _('status').innerHTML = "Firmware Upload!";
    _("loaded_n_total").innerHTML = "";
});