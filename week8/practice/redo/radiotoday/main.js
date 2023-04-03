function addGroupItem(title, timeLabel, content) {
    var newElement = document.createElement('a');
    newElement.setAttribute('href', '#');

    if (timeLabel.length != 0 & content.timeLabel != 0) {
        newElement.setAttribute('class', 'list-group-item list-group-item-action flex-column align-items-start');
        newElement.innerHTML = `
            <div class="d-flex w-100 justify-content-between">
                <h5 class="mb-1"><div style="color: tomato;">${title}</div></h5>
                <small class="text-muted">${timeLabel}</small>
            </div>
            <small class="mb-1">${content}</small>
        `;
        var listGroupDiv = document.getElementById('list-group-1');
        listGroupDiv.appendChild(newElement);
    }
    else {
        newElement.setAttribute('class', 'list-group-item');
        newElement.setAttribute('style', 'text-align: center; color: tomato')
        newElement.innerHTML = `${title}`;
        var listGroupDiv = document.getElementById('list-group-2');
        listGroupDiv.appendChild(newElement);
    }
}

addGroupItem("Rock and Roll On Tour", "Today", "Rock and Roll Hall of Fame and Museum OnTour Exhibit.");
addGroupItem("United Against Crime", "2 days ago", "Free videos, brochures and a quarterly teleconference focusing on Crime Prevention.");
addGroupItem("Home Security", "3 days ago", "How to protect your family from burglars and intruders.");
addGroupItem("TV/FM Reception", "5 days ago", "Answers to your Direct-to-Home, Outdoor and Indoor Reception questions.");
addGroupItem("Franchise Opportunities", "", "");
addGroupItem("Career Opportunities", "", "");

