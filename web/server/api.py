from .iplus1 import IPlus1Manager
from tastypie.authorization import DjangoAuthorization
from tastypie.resources import Resource
from tastypie import fields

class IPlus1Object(object):
    def __init__(self, native_lang='', target_lang='', deck='', iplus1_sentences=''):
        self.native_lang = native_lang
        self.target_lang = target_lang
        self.deck = deck
        self.iplus1_sentences = iplus1_sentences


class IPlus1Resource(Resource):
    native_lang = fields.CharField(attribute='native_lang')
    target_lang = fields.CharField(attribute='target_lang')
    deck = fields.CharField(attribute='deck')
    iplus1_sentences = fields.ListField(attribute='iplus1_sentences')

    class Meta:
        resource_name = 'iplus1'
        object_class = IPlus1Object
        authorization = DjangoAuthorization()
        always_return_data = True
        allowed_methods = ['post']

    def obj_create(self, bundle, request=None, **kwargs):
        print bundle.data
        
        native_lang = bundle.data['native_lang']
        target_lang = bundle.data['target_lang']
        deck = bundle.data['deck']

        iplus1 = IPlus1Manager()
        iplus1_sentences = iplus1.get_iplus1(deck, native_lang, target_lang)
        
        bundle.obj = IPlus1Object('','','', iplus1_sentences)
        return bundle


    # I have no idea what this is supposed to do
    # I just put in filler till it stopped complaining about me
    def detail_uri_kwargs(self, bundle):
        return [['', '']]
