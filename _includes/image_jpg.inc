{% assign image_id = image_id | plus: 1 %}<image src="{{ image_url }}/{{ page.date | date: '%Y-%m-%d-' }}{% if image_id < 10 %}0{% endif %}{{ image_id }}.jpg" />
