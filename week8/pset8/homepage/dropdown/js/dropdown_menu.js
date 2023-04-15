class dropdownMenu extends HTMLElement {
    constructor() {
        super();
        const placeholderText = this.getAttribute("placeholder");
        const withSearch = this.hasAttribute("with-search");

        // Create the dropdown-select element and set its attributes and classes
        const dropdownSelect = document.createElement('div');
        dropdownSelect.setAttribute('tabindex', '0');
        dropdownSelect.classList.add('dropdown-select', 'wide', 'unselected', ...this.classList);

        // Create the current element and add it to the dropdown-select element
        const current = document.createElement('span');
        current.classList.add('current');
        current.textContent = placeholderText;
        dropdownSelect.appendChild(current);

        // Create the list element and add it to the dropdown-select element
        const list = document.createElement('div');
        list.classList.add('list');
        dropdownSelect.appendChild(list);

        const dropdownOptions = this.querySelectorAll('dropdown-option');

        if (withSearch) {
            // Create the search element and add it before the ul element
            const searchDiv = document.createElement('div');
            searchDiv.classList.add('dd-search');
            const searchInput = document.createElement('input');
            searchInput.setAttribute('autocomplete', 'off');
            searchInput.setAttribute('type', 'text');
            searchInput.setAttribute('placeholder', 'Search DSP');
            searchInput.classList.add('dd-searchbox');
            searchDiv.appendChild(searchInput);
            list.appendChild(searchDiv);

            // Add search input listener to filter options according to the input
            searchInput.addEventListener('input', this.handleInputValidation);
            searchInput.addEventListener('keyup', this.filterDropdownOptions.bind(searchInput, dropdownOptions));
        }

        // Create the ul element and add it to the list element
        const ul = document.createElement('ul');
        list.appendChild(ul);

        // Move all dropdown-option elements to the ul element under the dropdown-select element
        dropdownOptions.forEach(option => {
            ul.appendChild(option);
        });

        // Add the dropdown-select element to the dropdown-menu element
        this.appendChild(dropdownSelect);

        // Add click listener to dropdown select element
        dropdownSelect.addEventListener('click', this.toggleDropdown);

        // Add click listener to document to close dropdown when clicking outside
        document.addEventListener('click', this.closeDropdown);

        // Add click listener to update `current` when an option is selected
        this.addEventListener('click', event => {
            const option = event.target.closest('.option');
            if (option) {
                this.selectOption(option);
            }
        });
    }

    handleInputValidation(event) {
        const input = event.target;
        input.value = input.value.replace(/[^a-zA-Z]/g, '');
    }

    toggleDropdown(event) {
        if (event.target.classList.contains('dd-searchbox')) {
            return;
        }
        document.querySelectorAll('.dropdown-select').forEach(dropdown => {
            if (dropdown !== this) {
                dropdown.classList.remove('open');
            }
        });

        this.classList.toggle('open');
        if (this.classList.contains('open')) {
            this.querySelectorAll('.option').forEach(option => option.setAttribute('tabindex', 0));
            const selectedOption = this.querySelector('.selected');
            if (selectedOption) {
                selectedOption.focus();
            }
        } else {
            this.querySelectorAll('.option').forEach(option => option.removeAttribute('tabindex'));
            this.focus();
        }
    }

    closeDropdown(event) {
        if (!event.target.closest('.dropdown-select')) {
            const dropdowns = document.querySelectorAll('.dropdown-select');
            for (const dropdown of dropdowns) {
                dropdown.classList.remove('open');
                const options = dropdown.querySelectorAll('.option');
                for (const option of options) {
                    option.removeAttribute('tabindex');
                }
            }
        }
    }

    filterDropdownOptions(dropdownOptions) {
        const searchValue = this.value;
        dropdownOptions.forEach((option) => {
            const optionText = option.textContent;
            const isOptionMatch = (optionText.toLowerCase().indexOf(searchValue.toLowerCase()) > -1);
            if (isOptionMatch) {
                option.style.display = '';
            } else {
                option.style.display = 'none';
            }
        });
    }

    selectOption(option) {
        // Find the relevant elements
        const list = option.closest('.list');
        const selected = list.querySelector('.selected');
        const selectedOption = option.cloneNode(true);
        const text = selectedOption.textContent;
        const image = selectedOption.querySelector('img')?.outerHTML || '';
        const dropdown = list.closest('.dropdown-select');
        const current = dropdown.querySelector('.current');

        // Update the UI
        selected?.classList.remove('selected');
        option.classList.add('selected');
        current.innerHTML = `
            ${image}
            <div>
                ${text}
            </div>
        `;
        dropdown.classList.remove('unselected');
        dropdown.classList.add('selected');
    }
}

customElements.define('dropdown-menu', dropdownMenu);
