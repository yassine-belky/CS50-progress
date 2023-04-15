class dropdownOption extends HTMLElement {
    constructor() {
        super();
        const [displayText, isSelected, dataValue, innerText, iconPath] = [
            this.dataset.displayText || '',
            this.selected ? 'selected' : '',
            this.getAttribute('value'),
            this.textContent,
            this.getAttribute('icon')
        ];

        const optionElem = document.createElement('li');
        optionElem.setAttribute('data-value', dataValue);
        optionElem.setAttribute('data-display-text', displayText);
        optionElem.textContent = innerText;

        const imgElem = document.createElement('img');
        imgElem.setAttribute('src', iconPath);

        const optionDiv = document.createElement('div');
        optionDiv.classList.add('option');
        if (isSelected) {
            optionDiv.classList.add(isSelected);
        }
        optionDiv.appendChild(imgElem);
        optionDiv.appendChild(optionElem);

        this.textContent = '';
        this.appendChild(optionDiv);
    }
}

customElements.define('dropdown-option', dropdownOption);