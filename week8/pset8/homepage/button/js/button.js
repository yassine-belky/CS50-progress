class Button extends HTMLElement {
    constructor() {
        super();
        const leftText = this.getAttribute('ltext');
        const rightText = this.getAttribute('rtext');
        this.innerHTML = `
            <div class="container">
                <div class="inner-container">
                    <div class="toggle">
                        <p>${rightText}</p>
                    </div>
                    <div class="toggle">
                        <p>${leftText}</p>
                    </div>
                </div>
                <div class="inner-container">
                    <div class="toggle">
                        <p>${rightText}</p>
                    </div>
                    <div class="toggle">
                        <p>${leftText}</p>
                    </div>
                </div>
            </div>
        `;
    }

    connectedCallback() {
        var container = this.querySelector('.container');
        container.style.visibility = 'hidden';
        setTimeout(() => {
            const [leftToggleWidth, rightToggleWidth] = this.setToggleWidths();
            this.setLeftToggleClipPath(rightToggleWidth);
            this.addToggleDynamics(leftToggleWidth, rightToggleWidth);
        }, 20);
    }

    setToggleWidths() {
        var containers = this.querySelectorAll('.container');
        let leftToggleWidth, rightToggleWidth;
        containers.forEach(function (container) {
            let autoContainerWidth = 0;
            let innerContainer = container.querySelector('.inner-container');
            let toggles = innerContainer.querySelectorAll('.toggle');

            for (let i = 0; i < toggles.length; i++) {
                let textElement = toggles[i].querySelector('p');
                let styles = getComputedStyle(textElement);
                let currentWidth = parseFloat(styles.width) + parseFloat(styles.marginLeft) + parseFloat(styles.marginRight);

                autoContainerWidth += currentWidth;
                toggles[i].style.width = `${currentWidth}px`;

                i == 1 ? leftToggleWidth = currentWidth : rightToggleWidth = currentWidth;
            }

            container.style.width = `${autoContainerWidth}px`;
            container.style.visibility = 'visible';
        });

        return [leftToggleWidth, rightToggleWidth];
    }

    setLeftToggleClipPath(rightToggleWidth) {
        let leftTogglesContainers = this.querySelectorAll('.inner-container:nth-child(2)');
        leftTogglesContainers.forEach(function (container) {
            container.style.clipPath = `inset(0 ${rightToggleWidth}px 0 0)`;
        });
    }

    addToggleDynamics(leftToggleWidth, rightToggleWidth) {
        var containers = this.querySelectorAll('.container');
        containers.forEach(function (container) {
            var toggleNumber;
            container.addEventListener('click', function () {
                toggleNumber = !toggleNumber;
                var innerContainers = container.querySelectorAll('.inner-container');
                var secondInnerContainer = innerContainers[1];
                if (toggleNumber) {
                    secondInnerContainer.style.clipPath = `inset(0 0 0 ${leftToggleWidth}px)`;
                    secondInnerContainer.style.backgroundColor = '#99f2bf';
                } else {
                    secondInnerContainer.style.clipPath = `inset(0 ${rightToggleWidth}px 0 0)`;
                    secondInnerContainer.style.backgroundColor = '#99f2bf';
                }
            });
        });
    }
}

customElements.define('toggle-button', Button);