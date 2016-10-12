from django.shortcuts import render
from django.shortcuts import render_to_response

from my_blog.models import Category, Blog


# Create your views here.
def index(request):
    return render_to_response('index.html',
        {
            'categories': Category.objects.all(),
            'posts': Blog.objects.all()[:8]
        })

def show_category(request):

    category = Category.objects.get(id=request.GET.get('id'))

    posts = Blog.objects.filter(category=category.id)

    return render_to_response('category.html',
        {
            'title': category.title,
            'body': category.body,
            'posts_in_category': posts
        })

def show_post(request):

    post = Blog.objects.get(id=request.GET.get('id'))

    return render_to_response('post.html',
        {
            'title': post.title,
            'body': post.body,
            'category': post.category,
            'posted': post.posted
        })
