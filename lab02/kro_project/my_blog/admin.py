from django.contrib import admin
from django.db import models
# Register your models here.

from my_blog.models import Blog, Category

# admin.site.register(Blog)

class BlogAdmin(admin.ModelAdmin):
    search_fields = ['title']
    list_display = ['title', 'posted']
    list_filter = ['posted']

admin.site.register(Blog, BlogAdmin)
admin.site.register(Category)
