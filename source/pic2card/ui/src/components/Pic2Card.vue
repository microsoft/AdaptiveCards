<template>
    <v-container>
        <v-row>
            <v-col>
                <p ref="cards"></p>
            </v-col>
            <v-col>
                <v-img
                    :src="image_data_url"
                    lazy-src="https://picsum.photos/510/300?random"
                    aspect-ratio="1"
                    class="grey lighten-2"
                    max-width="500"
                    max-height="300"
                    contain
                >
                    <template v-slot:placeholder>
                        <v-row
                            class="fill-height ma-0"
                            align="center"
                            justify="center"
                        >
                            <v-progress-circular
                                indeterminate
                                color="grey lighten-5"
                            ></v-progress-circular>
                        </v-row>
                    </template>
                </v-img>
            </v-col>
        </v-row>
    </v-container>
</template>

<script>
import * as AdaptiveCards from 'adaptivecards'
import AdaptiveCardApi from '@/services/ImageApi.js'
import Config from '@/components/config.js'
import MarkdownIt from 'markdown-it'

export default {
    name: 'Pic2Card',
    props: {
        base64_image: String
    },
    data() {
        return {
            image_str: this.base64_image,
            card_html: null,
            card_loading: true
        }
    },
    computed: {
        image_data_url() {
            return 'data:image/png;base64,' + this.image_str
        }
    },
    methods: {
        pic2Card(base64_image) {
            AdaptiveCardApi.getAdaptiveCard(base64_image).then(response => {
                // console.log(response.data)
                let card_json = response.data['card_json']

                // Add markdown rendering.
                AdaptiveCards.AdaptiveCard.onProcessMarkdown = function(
                    text,
                    result
                ) {
                    let md = new MarkdownIt()
                    result.outputHtml = md.render(text)
                    result.didProcess = true
                }

                let adaptiveCard = new AdaptiveCards.AdaptiveCard()
                adaptiveCard.hostConfig = new AdaptiveCards.HostConfig(
                    Config.adaptiveHostConfig
                )

                adaptiveCard.parse(card_json)
                this.card_html = adaptiveCard.render()
                this.$refs.cards.appendChild(this.card_html)

                // Also update the image that has bounding box.
                this.image_str = response.data['image']
            })
        },
        renderCard() {
            AdaptiveCardApi.getAdaptiveCard(this.image_str).then(response => {
                this.card_json = response.data['card_json']
            })
        }
    },
    mounted() {
        /**
         * Called after dom got attached.
         */
        this.$refs.cards.innerHTML = ''
        if (this.card_html) {
            this.$refs.cards.appendChild(this.card_html)
        }
    },
    beforeMount() {
        // Before dom attachment.
        // this.renderCard()
        this.pic2Card(this.image_str)
    }
}
</script>

<style scoped></style>
