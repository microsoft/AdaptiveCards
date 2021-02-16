<template>
    <v-app>
        <v-app-bar app color="blue-grey">
            <v-app-bar-nav-icon></v-app-bar-nav-icon>

            <v-toolbar-title>Pic2Card</v-toolbar-title>

            <v-spacer></v-spacer>

            <v-btn
                v-for="link in links"
                :key="`${link.label}-app-bar`"
                text
                rounded
                color="white"
                :to="link.url"
            >
                {{ link.label }}
            </v-btn>

            <v-btn icon>
                <v-icon>mdi-heart</v-icon>
            </v-btn>

            <v-btn icon>
                <v-icon>mdi-magnify</v-icon>
            </v-btn>

            <v-menu left bottom>
                <template v-slot:activator="{ on }">
                    <v-btn icon v-on="on">
                        <v-icon>mdi-dots-vertical</v-icon>
                    </v-btn>
                </template>

                <v-list>
                    <v-list-item v-for="n in 5" :key="n" @click="() => {}">
                        <v-list-item-title>Option {{ n }}</v-list-item-title>
                    </v-list-item>
                </v-list>
            </v-menu>
        </v-app-bar>

        <v-content>
            <router-view></router-view>
        </v-content>

        <v-footer color="blue-grey">
            <v-layout justify-center wrap>
                <v-btn
                    v-for="link in links"
                    :key="`${link.label}-footer-link`"
                    text
                    rounded
                    color="white"
                    class="my-2"
                    :to="link.url"
                >
                    {{ link.label }}
                </v-btn>
                <v-flex blue-grey py-4 text-center white--text xs12>
                    {{ new Date().getFullYear() }} —
                    <strong>Pic2Card</strong>
                </v-flex>
            </v-layout>
        </v-footer>
    </v-app>
</template>

<script>
// import HelloWorld from './components/HelloWorld'

export default {
    name: 'App',
    components: {
        // HelloWorld
    },

    data: () => ({
        links: [
            {
                label: 'Home',
                url: '/'
            }
        ]
    })
}
</script>
