function create_custom_dropdowns() {
    $('select').each(function (i, select) {
        if (!$(this).next().hasClass('dropdown-select')) {
            $(this).after(
                `
                    <div class="dropdown-select wide unselected ${$(this).attr('class') || ''}" tabindex="0">
                        <span class="current"></span>
                        <div class="list">
                            <ul></ul>
                        </div>
                    </div>
                `
            );

            const placeholderText = $(select).find('option:selected:disabled').text();
            var dropdown = $(this).next();
            var current = dropdown.find('.current');
            current.html(placeholderText);

            var options = $(select).find('option');
            options.each(function (j, option) {
                const [displayText, isSelected, isDisabled, dataValue, innerText, iconPath] = [
                    $(option).data('display-text') || '',
                    $(option).is(':selected') ? 'selected' : '',
                    $(option).is(':disabled') ? 'disabled' : '',
                    $(option).val(),
                    $(option).text(),
                    $(option).attr('icon')
                ];
                if (!isDisabled) {
                    dropdown.find('ul').append(
                        `
                            <div class="option ${isSelected}">
                                <img src="${iconPath}">
                                <li data-value="${dataValue}" data-display-text="${displayText}">
                                    ${innerText}
                                </li>
                            </div>
                        `
                    );
                }
            });
        }
    });

    $('.dropdown-select ul').before(
        `
            <div class="dd-search">
                <input id="searchInput" autocomplete="off" onkeyup="filterDropdownOptions()" class="dd-searchbox" type="text" placeholder="Search DSP">
            </div>
        `
    );
}

// Open/close
$(document).on('click', '.dropdown-select', function (event) {
    if ($(event.target).hasClass('dd-searchbox')) {
        return;
    }
    $('.dropdown-select').not($(this)).removeClass('open');
    $(this).toggleClass('open');
    if ($(this).hasClass('open')) {
        $(this).find('.option').attr('tabindex', 0);
        $(this).find('.selected').focus();
    } else {
        $(this).find('.option').removeAttr('tabindex');
        $(this).focus();
    }
});

// Close when clicking outside
$(document).on('click', function (event) {
    if ($(event.target).closest('.dropdown-select').length === 0) {
        $('.dropdown-select').removeClass('open');
        $('.dropdown-select .option').removeAttr('tabindex');
    }
    event.stopPropagation();
});

function filterDropdownOptions() {
    var searchValue = $('#searchInput').val();
    $('.dropdown-select ul > .option').each(function () {
        var optionText = $(this).text();
        var isOptionMatch = (optionText.toLowerCase().indexOf(searchValue.toLowerCase()) > -1);
        var isOptionDisabled = $(this).hasClass('disabled');
        if (isOptionMatch && !isOptionDisabled) {
            $(this).show();
        } else {
            $(this).hide();
        }
    });
};

// Option click
$(document).on('click', '.dropdown-select .option', function (event) {
    $(this).closest('.list').find('.selected').removeClass('selected');
    $(this).addClass('selected');
    var selectedOption = $(this).clone();
    var text = selectedOption.text(); // get the HTML content of the cloned .option element
    var image = selectedOption.find('img').prop('outerHTML'); // get the HTML content of the <img> element
    var dropdown = $(this).closest('.dropdown-select');
    dropdown.find('.current').html(`${image}<div>${text}</div>`); // wrap the text content in a <div> element and add it to the .current element
    dropdown.removeClass('unselected').addClass('selected');
    dropdown.prev('select').val($(this).data('value')).trigger('change');
});

$(document).ready(function () {
    create_custom_dropdowns();
});