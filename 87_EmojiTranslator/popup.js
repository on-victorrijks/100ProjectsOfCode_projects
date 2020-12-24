function injectTheScript() {
    chrome.tabs.query({active: true, currentWindow: true}, function(tabs) {
        chrome.tabs.executeScript(tabs[0].id, {file: "content_script.js"});
    });

    btn = document.getElementById('translate');

    btn.innerHTML = 'Done!';
    btn.style.backgroundColor = "#2ecc71";

}

document.getElementById('translate').addEventListener('click', injectTheScript);

