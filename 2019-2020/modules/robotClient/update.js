
function callRest() {
    var apiUrl = "http://localhost:3001/status";
    fetch(apiUrl).then(response => {
        var data = {};

        if (response.status != 200) {
            data.status = response.status;
            data.cors = response.cors;
            data.url = response.url;
        }
        else
            data = response.json();

        return data;
    }).then(data => {
        var html = '';
        try {
            var json = JSON.stringify(data, undefined, 2);
            html = json;
            //html = syntaxHighlight(json);
        } catch (e1) {
            html = e1;
        }
        $('#result').html(html);
    }).catch(err => {
        if (err.message == 'Failed to fetch')
            $('#result').html(`${err.message} : Possible Reasons for no connection:<br>* The URL may not be listening<br>* Required parameters are missing<br>* The port could be wrong<br>* The service may need to have cors enabled in the web.conf`)
        else
            $('#result').html(err.message);
    });
}