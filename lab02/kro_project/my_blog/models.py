from __future__ import unicode_literals

from django.db import models

class Blog(models.Model):
    title = models.CharField(max_length=100, unique=True)
    body = models.TextField()
    posted = models.DateTimeField(auto_now_add=True)
    category = models.ForeignKey('Category', on_delete=models.CASCADE)

    def __unicode__(self):
        return '%s' % self.title

class Category(models.Model):
    title = models.CharField(max_length=100, unique=True)
    body = models.TextField()

    def __unicode__(self):
        return '%s' % self.title
