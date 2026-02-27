export class BadgesComponent {
  constructor(parent) {
      this.parent = parent;
  }

  getHTML(category) {
      const badgeColors = {
          'Мясо': 'bg-danger',
          'Овощи': 'bg-success',
          'Фрукты': 'bg-warning',
          'Молочные Продукты': 'bg-info',
          'Грибы': 'bg-secondary'
      };

      return (
          `
              <span class="badge ${badgeColors[category]}">${category}</span>
          `
      )
  }

  render(category) {
      const html = this.getHTML(category)
      this.parent.insertAdjacentHTML('beforeend', html)
  }
}